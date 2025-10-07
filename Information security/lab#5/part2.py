"""
DES wrapper that imports helper functions from lab#4 and lab#5 and
provides desEncryption and desDecryption functions.

Usage:
  from part2 import desEncryption, desDecryption
  ct = desEncryption('Hello', '133457799BBCDFF1')
  pt = desDecryption(ct, '133457799BBCDFF1')
"""

from typing import List
import os
import importlib.util
import sys

# Local tables needed for expansion and key schedule
E_TABLE = [
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
]

PC1 = [
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
]

PC2 = [
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
]

LEFT_SHIFTS = [1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1]


def load_func_from(path: str, func_name: str):
    path = os.path.normpath(path)
    spec = importlib.util.spec_from_file_location(func_name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return getattr(mod, func_name)


# locate lab folders relative to this file
HERE = os.path.dirname(os.path.abspath(__file__))
LAB4 = os.path.normpath(os.path.join(HERE, '..', 'lab#4'))
LAB5 = os.path.normpath(os.path.join(HERE, '..', 'lab#5'))

# import functions from lab#4 and lab#5
def _load_lab4_modules():
    # load task1 first and make it available as 'task1' so task2 imports work
    task1_path = os.path.join(LAB4, 'task1.py')
    task2_path = os.path.join(LAB4, 'task2.py')
    task3_path = os.path.join(LAB4, 'task3.py')

    spec1 = importlib.util.spec_from_file_location('lab4_task1', task1_path)
    mod1 = importlib.util.module_from_spec(spec1)
    spec1.loader.exec_module(mod1)
    # temporarily register as 'task1' so relative imports in lab files resolve
    sys.modules['task1'] = mod1

    spec2 = importlib.util.spec_from_file_location('lab4_task2', task2_path)
    mod2 = importlib.util.module_from_spec(spec2)
    spec2.loader.exec_module(mod2)

    spec3 = importlib.util.spec_from_file_location('lab4_task3', task3_path)
    mod3 = importlib.util.module_from_spec(spec3)
    spec3.loader.exec_module(mod3)

    return mod1, mod2, mod3


lab4_mod1, lab4_mod2, lab4_mod3 = _load_lab4_modules()
desPlaintextBlock = getattr(lab4_mod1, 'desPlaintextBlock')
desInitialPermutation = getattr(lab4_mod2, 'desInitialPermutation')
desFinalPermutation = getattr(lab4_mod3, 'desFinalPermutation')

# load lab#5 functions (they don't depend on lab#4 by absolute names)
getSubBoxes = load_func_from(os.path.join(LAB5, 'task2.py'), 'getSubBoxes')
desRoundPermutation = load_func_from(os.path.join(LAB5, 'task3.py'), 'desRoundPermutation')


def permute(bits: str, table: List[int]) -> str:
    return ''.join(bits[i-1] for i in table)


def xor_bits(a: str, b: str) -> str:
    return ''.join('1' if x!=y else '0' for x,y in zip(a,b))


def bits_from_hex(h: str) -> str:
    value = int(h, 16)
    bitlen = len(h) * 4
    return format(value, '0{}b'.format(bitlen))


def hex_from_bits(b: str) -> str:
    return '{:0{}x}'.format(int(b, 2), len(b)//4)


def bits_to_str(b: str) -> str:
    chars = [b[i:i+8] for i in range(0, len(b), 8)]
    return ''.join(chr(int(ch, 2)) for ch in chars)


def generate_round_keys(key64_bits: str) -> List[str]:
    key56 = permute(key64_bits, PC1)
    C = key56[:28]
    D = key56[28:]
    round_keys = []
    for shift in LEFT_SHIFTS:
        C = C[shift:] + C[:shift]
        D = D[shift:] + D[:shift]
        combined = C + D
        round_key = permute(combined, PC2)
        round_keys.append(round_key)
    return round_keys


def sbox_substitution_using_lab(bitstring48: str) -> str:
    bits_list = [int(b) for b in bitstring48]
    return getSubBoxes(bits_list)


def p_permutation_using_lab(block32_str: str) -> str:
    bits_list = [int(b) for b in block32_str]
    permuted_list = desRoundPermutation(bits_list)
    return ''.join(str(x) for x in permuted_list)


def feistel(right32: str, round_key48: str) -> str:
    expanded = permute(right32, E_TABLE)
    xored = xor_bits(expanded, round_key48)
    sboxed = sbox_substitution_using_lab(xored)
    permuted = p_permutation_using_lab(sboxed)
    return permuted


def des_encrypt_block(block64: str, round_keys: List[str]) -> str:
    ip = desInitialPermutation(block64)
    L = ip[:32]
    R = ip[32:]
    for k in round_keys:
        newL = R
        newR = xor_bits(L, feistel(R, k))
        L, R = newL, newR
    preoutput = R + L
    cipher = desFinalPermutation(preoutput)
    return cipher


def des_decrypt_block(block64: str, round_keys: List[str]) -> str:
    return des_encrypt_block(block64, list(reversed(round_keys)))


def desEncryption(plaintext: str, key64_hex: str) -> str:
    key_bits = bits_from_hex(key64_hex)
    round_keys = generate_round_keys(key_bits)
    blocks = desPlaintextBlock(plaintext)
    cipher_bits = ''
    for blk in blocks:
        cipher_bits += des_encrypt_block(blk, round_keys)
    return hex_from_bits(cipher_bits)


def desDecryption(ciphertext_hex: str, key64_hex: str) -> str:
    key_bits = bits_from_hex(key64_hex)
    round_keys = generate_round_keys(key_bits)
    bits = bits_from_hex(ciphertext_hex)
    plaintext_bits = ''
    for i in range(0, len(bits), 64):
        block = bits[i:i+64]
        plaintext_bits += des_decrypt_block(block, round_keys)
    return bits_to_str(plaintext_bits)


if __name__ == '__main__':
    sample_plain = 'Hello DES'
    sample_key = '133457799BBCDFF1'
    print('Plaintext:', sample_plain)
    ct = desEncryption(sample_plain, sample_key)
    print('Ciphertext (hex):', ct)
    pt = desDecryption(ct, sample_key)
    print('Decrypted:', pt)
"""
Simple DES implementation for lab: desEncryption and desDecryption

This file implements the necessary DES primitives (IP, FP, E, P, S-boxes,
key schedule using PC-1/PC-2 and left shifts) and provides two helpers:
 - desEncryption(plaintext, key) : returns ciphertext as hex string
 - desDecryption(ciphertext_hex, key) : returns plaintext string

Note: This implementation operates on ASCII plaintext and uses zero-padding
to fill the last 64-bit block (matches earlier lab helpers).
"""

from typing import List
"""
DES wrapper that imports helper functions from lab#4 and lab#5.

This file wires the existing lab implementations for block splitting,
initial/final permutations, S-boxes and round permutation into a
complete desEncryption/desDecryption API.
"""

from typing import List
import os
import importlib.util

# Tables used locally
E_TABLE = [
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
]

PC1 = [
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
]

PC2 = [
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
]

LEFT_SHIFTS = [1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1]


def load_func_from(path: str, func_name: str):
    path = os.path.normpath(path)
    spec = importlib.util.spec_from_file_location(func_name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return getattr(mod, func_name)


# compute sibling folder paths
HERE = os.path.dirname(os.path.abspath(__file__))
LAB4 = os.path.normpath(os.path.join(HERE, '..', 'lab#4'))
LAB5 = os.path.normpath(os.path.join(HERE, '..', 'lab#5'))

# load functions implemented in earlier labs
desPlaintextBlock = load_func_from(os.path.join(LAB4, 'task1.py'), 'desPlaintextBlock')
desInitialPermutation = load_func_from(os.path.join(LAB4, 'task2.py'), 'desInitialPermutation')
desFinalPermutation = load_func_from(os.path.join(LAB4, 'task3.py'), 'desFinalPermutation')
getSubBoxes = load_func_from(os.path.join(LAB5, 'task2.py'), 'getSubBoxes')
desRoundPermutation = load_func_from(os.path.join(LAB5, 'task3.py'), 'desRoundPermutation')


def str_to_bits(s: str) -> str:
    return ''.join(format(ord(c), '08b') for c in s)


def bits_to_str(b: str) -> str:
    chars = [b[i:i+8] for i in range(0, len(b), 8)]
    return ''.join(chr(int(ch, 2)) for ch in chars)


def hex_from_bits(b: str) -> str:
    return '{:0{}x}'.format(int(b, 2), len(b)//4)


def bits_from_hex(h: str) -> str:
    value = int(h, 16)
    bitlen = len(h) * 4
    return format(value, '0{}b'.format(bitlen))


def permute(bits: str, table: List[int]) -> str:
    return ''.join(bits[i-1] for i in table)


def xor_bits(a: str, b: str) -> str:
    return ''.join('1' if x!=y else '0' for x,y in zip(a,b))


def generate_round_keys(key64_bits: str) -> List[str]:
    key56 = permute(key64_bits, PC1)
    C = key56[:28]
    D = key56[28:]
    round_keys = []
    for shift in LEFT_SHIFTS:
        C = C[shift:] + C[:shift]
        D = D[shift:] + D[:shift]
        combined = C + D
        round_key = permute(combined, PC2)
        round_keys.append(round_key)
    return round_keys


def sbox_substitution_using_lab(bitstring48: str) -> str:
    bits_list = [int(b) for b in bitstring48]
    return getSubBoxes(bits_list)


def p_permutation_using_lab(block32_str: str) -> str:
    bits_list = [int(b) for b in block32_str]
    permuted_list = desRoundPermutation(bits_list)
    return ''.join(str(x) for x in permuted_list)


def feistel(right32: str, round_key48: str) -> str:
    expanded = permute(right32, E_TABLE)
    xored = xor_bits(expanded, round_key48)
    sboxed = sbox_substitution_using_lab(xored)
    permuted = p_permutation_using_lab(sboxed)
    return permuted


def des_encrypt_block(block64: str, round_keys: List[str]) -> str:
    ip = desInitialPermutation(block64)
    L = ip[:32]
    R = ip[32:]
    for k in round_keys:
        newL = R
        newR = xor_bits(L, feistel(R, k))
        L, R = newL, newR
    preoutput = R + L
    cipher = desFinalPermutation(preoutput)
    return cipher


def des_decrypt_block(block64: str, round_keys: List[str]) -> str:
    return des_encrypt_block(block64, list(reversed(round_keys)))


def desEncryption(plaintext: str, key64_hex: str) -> str:
    key_bits = bits_from_hex(key64_hex)
    round_keys = generate_round_keys(key_bits)
    blocks = desPlaintextBlock(plaintext)
    cipher_bits = ''
    for blk in blocks:
        cipher_bits += des_encrypt_block(blk, round_keys)
    return hex_from_bits(cipher_bits)


def desDecryption(ciphertext_hex: str, key64_hex: str) -> str:
    key_bits = bits_from_hex(key64_hex)
    round_keys = generate_round_keys(key_bits)
    bits = bits_from_hex(ciphertext_hex)
    plaintext_bits = ''
    for i in range(0, len(bits), 64):
        block = bits[i:i+64]
        plaintext_bits += des_decrypt_block(block, round_keys)
    return bits_to_str(plaintext_bits)


if __name__ == '__main__':
    sample_plain = 'Hello DES'
    sample_key = '133457799BBCDFF1'
    print('Plaintext:', sample_plain)
    ct = desEncryption(sample_plain, sample_key)
    print('Ciphertext (hex):', ct)
    pt = desDecryption(ct, sample_key)
    print('Decrypted:', pt)

