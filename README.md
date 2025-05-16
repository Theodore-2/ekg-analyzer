
# EKG Classification and Peak Analysis in C++

This project reads raw EKG data from `.txt` files, detects peaks, classifies them based on heart rate (bradycardia, normal, or tachycardia), and outputs the classified data to separate text files. It also provides merged output files for easier comparison.

## 🧠 Features

- Peak detection using local maxima with filtering
- Heart rate classification:
  - **Bradycardia**: RR interval > 1.0s
  - **Normal**: RR interval between 0.6s and 1.0s
  - **Tachycardia**: RR interval < 0.6s
- Outputs classification results to separate files
- Merges classification results across multiple individuals

## 🗂️ File Structure

- `person1.txt`, `person2.txt`, `person3.txt`: Input raw EKG data
- `*-normal.txt`, `*-bradycardia.txt`, `*-tachycardia.txt`: Classified outputs
- `normal-person-1-2-3.txt`, `bradycardia-person-1-2-3.txt`, `tachycardia-person-1-2-3.txt`: Combined results

## ⚙️ How to Run

1. Compile the program:

```bash
g++ ekg_analysis.cpp -o ekg_analysis
```

2. Place your input files (`person1.txt`, `person2.txt`, etc.) in the same directory.
3. Run the executable:

```bash
./ekg_analysis
```

## 📊 Sample Output

Each output file contains:

```text
TIME           VOLTAGE
------------------------------
0.9200         0.0752
1.9200         0.0748
...
```

## 🧪 Dependencies

Standard C++ library (no external dependencies)

## 📌 Notes

- Ensure `.txt` files are properly formatted (time and voltage per line).
- Header lines are ignored automatically.

---

**Developed by**: Arda Çimen (The Engineer)
