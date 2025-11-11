from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import serialization

# public exponent is typically 65537
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048  
)

public_key = private_key.public_key()


pem_private_key = private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)

with open('private.pem', 'wb') as f:
    f.write(pem_private_key)

print("private.pem file generated.")

# --- Save the public key ---
pem_public_key = public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

with open('public.pem', 'wb') as f:
    f.write(pem_public_key)

print("public.pem file generated.")