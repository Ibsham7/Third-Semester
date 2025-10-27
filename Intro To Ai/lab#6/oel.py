import pandas as pd
import heapq
import matplotlib.pyplot as plt
import datetime
import os


CITY_SIZE = 10
FIRE_STATIONS = [(1, 1), (10, 10)] 
SEGMENT_LENGTH_KM = 1.0  # we assume each road segment is 1 km


def parse_coordinates(coord_str):
    if isinstance(coord_str, str):
        coord_str = coord_str.strip().replace('(', '').replace(')', '')
        x, y = map(int, coord_str.split(','))
        return (x, y)
    return tuple(coord_str)

def load_data(excel_path):
    road_df = pd.read_excel(excel_path, sheet_name='road_traffic_data')
    emer_df = pd.read_excel(excel_path, sheet_name='Emergency Site')

    road_df['Road Segment Start'] = road_df['Road Segment Start'].apply(parse_coordinates)
    road_df['Road Segment End'] = road_df['Road Segment End'].apply(parse_coordinates)

    def time_to_hours(t):
        if isinstance(t, datetime.time):
            return t.hour + t.minute / 60.0
        elif pd.isna(t):
            return None
        else:
            return float(t)
    
    road_df['Time'] = road_df['Time'].apply(time_to_hours)
    emer_df['Coordinates'] = emer_df['Coordinates'].apply(parse_coordinates)
    emer_df['Time'] = emer_df['Time'].apply(time_to_hours)

    return road_df, emer_df


def build_graph(road_df, snapshot_time):
    graph = {}

    available = road_df[road_df['Time'] <= snapshot_time]
    
    if available.empty:
        available = road_df

    filtered = available.sort_values('Time').groupby(['Road Segment Start', 'Road Segment End']).tail(1)

    for _, row in filtered.iterrows():
        u, v = row['Road Segment Start'], row['Road Segment End']
        speed = row['Current Speed (km/h)']
        status = str(row['Status']).lower().strip() if not pd.isna(row['Status']) else 'open'

        if pd.isna(speed) or speed <= 0:
            continue
        
        if status == 'blocked':
            speed *= 0.5  # i have assumed block as traffic jam and road blocks which slows down speed as in real world scenario blocked can mean traffic jam
                          #it doesnt mean the road completely closed
        
        travel_time = 60.0 * SEGMENT_LENGTH_KM / speed
        graph.setdefault(u, []).append((v, travel_time))
        graph.setdefault(v, []).append((u, travel_time))

    return graph


  


def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def find_reachable_nodes(graph, start):
    if start not in graph:
        return set()
    
    visited = {start}
    queue = [start]
    
    while queue:
        current = queue.pop(0)
        for neighbor, _ in graph.get(current, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return visited

def find_nearest_node(graph, target):
    if target in graph:
        return target
    
    if not graph:
        return None
    
    min_dist = float('inf')
    nearest = None
    for node in graph:
        dist = heuristic(node, target)
        if dist < min_dist:
            min_dist = dist
            nearest = node
    return nearest

def a_star(graph, start, goal):
    open_set = []
    heapq.heappush(open_set, (0, start))
    came_from = {}
    g_score = {start: 0}

    while open_set:
        _, current = heapq.heappop(open_set)
        if current == goal:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            path.reverse()
            return path, g_score[goal]

        for neighbor, cost in graph.get(current, []):
            tentative_g = g_score[current] + cost
            if neighbor not in g_score or tentative_g < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g
                f_score = tentative_g + heuristic(neighbor, goal)
                heapq.heappush(open_set, (f_score, neighbor))

    return None, float('inf')


def dispatch_fire_truck(road_df, emergency_calls):
    results = []
    
    for _, call in emergency_calls.iterrows():
        emergency_site = call['Coordinates']
        call_time = call['Time']

        graph = build_graph(road_df, call_time)
        
        # Find nearest graph node to emergency site
        emergency_node = find_nearest_node(graph, emergency_site)
        if emergency_node is None:
            print(f"Warning: Cannot find any node in graph for emergency at {emergency_site}")
            results.append({
                'Emergency Site': emergency_site,
                'Best Station': None,
                'Travel Time (min)': float('inf'),
                'Path': []
            })
            continue

        best_station, best_time, best_path = None, float('inf'), []

        for station in FIRE_STATIONS:
            # Find nearest graph node to fire station
            station_node = find_nearest_node(graph, station)
            if station_node is None:
                continue
            
            path, travel_time = a_star(graph, station_node, emergency_node)
            if travel_time < best_time:
                best_station, best_time, best_path = station, travel_time, path

        results.append({
            'Emergency Site': emergency_site,
            'Best Station': best_station,
            'Travel Time (min)': best_time,
            'Path': best_path
        })
    return results

#  VISUALIZATION
# ===============================
def plot_route(path, emergency_site, station):
    grid_x = [x for x in range(1, CITY_SIZE + 1)]
    grid_y = [y for y in range(1, CITY_SIZE + 1)]

    plt.figure(figsize=(6, 6))
    for x in grid_x:
        plt.plot([x]*len(grid_y), grid_y, 'lightgray', linewidth=0.5)
    for y in grid_y:
        plt.plot(grid_x, [y]*len(grid_x), 'lightgray', linewidth=0.5)

    if path:
        xs, ys = zip(*path)
        plt.plot(xs, ys, '-o', color='red', label='Optimal Path')

    plt.scatter(*station, color='blue', label='Fire Station', s=100)
    plt.scatter(*emergency_site, color='green', label='Emergency Site', s=100)

    plt.title(f"A* Route from {station} to {emergency_site}")
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.grid(True)
    plt.show()

# ===============================

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    excel_path = os.path.join(script_dir, 'lab 7 - data file.xlsx')
    road_df, emer_df = load_data(excel_path)
    results = dispatch_fire_truck(road_df, emer_df)

    results_data = []
    for i, result in enumerate(results, 1):
        results_data.append({
            'Emergency #': i,
            'Emergency Site': str(result['Emergency Site']),
            'Best Station': str(result['Best Station']) if result['Best Station'] else 'N/A',
            'Travel Time (min)': result['Travel Time (min)'] if result['Travel Time (min)'] != float('inf') else 'N/A',
            'Path Length': len(result['Path']) if result['Path'] else 0,
            'Path': ' -> '.join([str(node) for node in result['Path']]) if result['Path'] else 'No path found'
        })
    
    results_df = pd.DataFrame(results_data)
    
    # Save to CSV
    csv_path = os.path.join(script_dir, 'result.csv')
    results_df.to_csv(csv_path, index=False)
    print(f"\n{'='*80}")
    print(f"Results saved to: {csv_path}")
    print(f"{'='*80}\n")
    
    # Display table
    print("FIRE TRUCK DISPATCH RESULTS")
    print("="*80)
    
    # Print table header
    print(f"{'#':<4} {'Emergency Site':<18} {'Best Station':<15} {'Travel Time':<15} {'Path Length':<12} {'Status':<10}")
    print("-"*80)
    
    # Print each row
    for _, row in results_df.iterrows():
        travel_time = f"{row['Travel Time (min)']:.2f} min" if row['Travel Time (min)'] != 'N/A' else 'N/A'
        status = 'SUCCESS' if row['Travel Time (min)'] != 'N/A' else 'NO PATH'
        print(f"{row['Emergency #']:<4} {row['Emergency Site']:<18} {row['Best Station']:<15} {travel_time:<15} {row['Path Length']:<12} {status:<10}")
    
    print("="*80)
    
    # Summary statistics
    successful = len([r for r in results if r['Best Station'] is not None])
    failed = len(results) - successful
    avg_time = sum([r['Travel Time (min)'] for r in results if r['Travel Time (min)'] != float('inf')]) / successful if successful > 0 else 0
    
    print(f"\nSUMMARY:")
    print(f"  Total Emergencies: {len(results)}")
    print(f"  Successfully Dispatched: {successful}")
    print(f"  Failed (No Path): {failed}")
    print(f"  Average Travel Time: {avg_time:.2f} minutes")
    print(f"{'='*80}\n")
    
    # Visualize routes for successful dispatches
    print("Displaying route visualizations for successful dispatches...\n")
    for result in results:
        if result['Best Station'] is not None and result['Path']:
            plot_route(result['Path'], result['Emergency Site'], result['Best Station'])


if __name__ == '__main__':
    main()
