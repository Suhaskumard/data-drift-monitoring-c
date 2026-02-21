Data Drift Monitoring System (C)
A console-based Data Drift Monitoring System written in C that detects statistical changes in incoming data over time. The project is inspired by AI/ML observability platforms used to ensure data stability and reliability in production systems.

📊 Project Overview
This system establishes a baseline dataset and continuously compares new incoming data against it. By monitoring statistical properties such as mean and standard deviation, the system identifies whether the data distribution has changed (data drift).

If drift exceeds defined thresholds, the system:

Classifies the drift severity

Raises alerts

Logs events with timestamps for auditing and analysis

✨ Features
Baseline data profiling

Mean and standard deviation calculation

Percentage-based drift detection

Severity classification:

🟢 Low Drift

🟡 Medium Drift

🔴 High Drift

Multiple monitoring cycles (stream simulation)

Timestamped alert logging

Summary dashboard with stability score

Single-file C implementation

🧠 Concepts Used
Structures (struct)

Arrays and loops

Statistical calculations

Conditional logic

File handling (fopen, fprintf)

Time and logging

Modular programming in C

📁 Project Structure
Plaintext
data-drift-monitoring-c/
│── drift_monitor.c
│── drift_log.txt        # Auto-generated after first run
│── README.md
Note: drift_log.txt is created automatically when the program is executed.

⚙️ How to Compile & Run
Ensure you have GCC installed.

Linux / macOS / Git Bash (Windows)
Bash
gcc drift_monitor.c -o drift
./drift
Windows (Command Prompt / PowerShell)
DOS
gcc drift_monitor.c -o drift.exe
drift.exe
🎯 How It Works
User provides baseline data values.

System calculates baseline statistics.

New data is collected over multiple monitoring cycles.

Current statistics are compared against the baseline.

Drift percentage is computed.

Alerts are generated if thresholds are exceeded.

Results are logged and summarized.

📊 Output Summary
At the end of execution, the system displays:

Total monitoring checks

Count of low, medium, and high drift events

Overall data stability score

Location of the drift log file

🚀 Future Enhancements
CSV file input support

Feature-wise drift detection

Rolling window statistics

Automatic baseline recalibration

ASCII trend charts

🎓 Academic & Portfolio Use
This project is suitable for:

C programming mini-projects

Rare and modern academic topics

AI/ML observability concept demonstration

GitHub portfolios

Viva and technical interviews

📜 License
This project is for educational purposes and is open for learning and modification.
