Bitcoin Puzzle Cracker A live website is in development to display real-time scanning progress
![image](https://github.com/user-attachments/assets/3b82ca9f-9759-4da2-affa-2fee827be174)
Steps to Set Up the Python Script:
Install Missing Libraries
Run the script first—it will show errors if libraries are missing.
Install each required library one by one using pip.
Modify File Paths (Puzzles 35 & 71)
In the script, locate Puzzle 35 and Puzzle 71.
Change the default folder paths to match your own directory (where your files are stored).
Example: Replace CUDA_CRACK_PATH = r"C:\Users\pc\Desktop\PuzzleBTC\cubitcrack.exe"... with D:/your_project/folder/....
Example: Replace WORK_DIR = r"C:\Users\pc\Desktop\PuzzleBTC"... with D:/your_project/folder/....
Add Your Bitcoin Address
Find the user_id or BTC address field in the script.
Replace the placeholder with your own Bitcoin address.
Check Reference Images (if needed)

![image](https://github.com/user-attachments/assets/b58a358f-ff0a-40e3-9fb8-fb9bdfb5d1a1)

This program is designed to crack Puzzle #71 by efficiently scanning and processing hexadecimal codes. Here's a clear explanation of how it works:

How the Program Works:
Scanning & Pool Collection

The program scans 8-digit hexadecimal codes (from a shared pool) and checks them against Puzzle 71, which consists of 18 hex characters.

The first 8 digits are taken from the pool (to avoid duplicate scans).

The remaining 10 digits are generated sequentially for exhaustive testing.

Avoiding Duplicates

Once a code is scanned, it is stored in the pool so that it is never scanned again, improving efficiency.

High-Speed Processing

Currently, this is the fastest known script for cracking Puzzle 71.

Users are encouraged to join forces to collectively solve the puzzle faster.

Testing & Verification

You can test the script on Puzzle #35 before applying it to Puzzle 71.

If a match is found, the program creates a found.txt file with the solution.

Future Development

A live website is in development to display real-time scanning progress.

The goal is to create a collaborative platform for puzzle-solving.

1. When an External Participant Solves the Puzzle
Solver (Winner): Receives 90% of the prize.

Developer: Receives 10% (for maintenance/server costs).

Other Contributors: Do not receive a share in this scenario.

2. When the Developer Solves the Puzzle
100% of the prize is distributed among all active contributors.

Each contributor’s share is proportional to their scan count (e.g., if you performed 5% of total scans, you get 5% of the prize).

Developer is treated as a regular contributor (receives a share based on their scans).

Current Status
The program is fully functional and optimized for Puzzle 71.

More features (like the live tracking website) are coming soon.

Support the Developer
Donations are greatly appreciated and will help improve the project!

BTC: bc1qshjmmq898m7mwceyr4qlk3vz0ptxue3yd8ux2y
ETH: 0xA6BCdcD154e704f9fcEc2996A8c5ACc76C56A184

If you’d like to contribute to the website and help speed up the process, your support is warmly welcome!
