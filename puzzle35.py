import os
import random
import subprocess

# Configuratie
CUDA_CRACK_PATH = r"C:\Users\pc\Desktop\PuzzleBTC\cubitcrack.exe"
INPUT_FILE = "puzzle.txt"
OUTPUT_FILE = "FOUND.txt"
BASE_DIR = r"C:\Users\pc\Desktop\PuzzleBTC"

PREFIXES = ['4', '5', '6', '7']

def generate_random_hex(length):
    return ''.join(random.choice('0123456789abcdef') for _ in range(length))

def process_prefix(prefix):
   
    while True:
        extended_prefix = prefix + generate_random_hex(0)
        start = f"{extended_prefix}00000000"
        end = f"{extended_prefix}ffffffff"
        
        cmd = [
            CUDA_CRACK_PATH,
            "-c",
            "-i", INPUT_FILE,
            "-o", OUTPUT_FILE,
            "--keyspace", f"{start}:{end}",
            "--stride", "1"
        ]
        
        print(f"[{prefix}] Nieuwe range: {start}:{end}")
        result = subprocess.run(cmd, cwd=BASE_DIR)
        
        if result.returncode != 0:
            print(f"[{prefix}] Fout gedetecteerd, opnieuw proberen...")
            continue
        
       

def main():
    os.chdir(BASE_DIR)
    
    
    for prefix in PREFIXES:
        print(f"Beginnen met verwerken van prefix: {prefix}")
        process_prefix(prefix)
        print(f"Voltooid verwerken van prefix: {prefix}, ga verder met volgende...")
    
    print("Alle prefixes zijn verwerkt! Herstarten...")
    

    main()

if __name__ == "__main__":
    main()