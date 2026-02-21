#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_DATA 100
#define LOW_THRESHOLD 10.0     // % drift
#define HIGH_THRESHOLD 25.0    // % drift
#define LOG_FILE "drift_log.txt"

/* ---------- STRUCTURES ---------- */
typedef struct {
    double mean;
    double std;
    double min;
    double max;
} Stats;

typedef struct {
    int totalChecks;
    int lowDrift;
    int mediumDrift;
    int highDrift;
} Summary;

/* ---------- FUNCTION DECLARATIONS ---------- */
void collectData(double data[], int n);
Stats calculateStats(double data[], int n);
double percentChange(double base, double current);
void checkDrift(Stats baseline, Stats current, Summary *summary);
void logEvent(const char *severity, double meanDrift, double stdDrift);
void showSummary(Summary summary);

/* ---------- MAIN ---------- */
int main() {
    double data[MAX_DATA];
    int n, cycles;
    Summary summary = {0, 0, 0, 0};

    printf("=====================================\n");
    printf("   DATA DRIFT MONITORING SYSTEM (C)\n");
    printf("=====================================\n");

    printf("Enter number of baseline data points: ");
    scanf("%d", &n);

    collectData(data, n);
    Stats baseline = calculateStats(data, n);

    printf("\nBaseline Statistics:\n");
    printf("Mean: %.2f | Std: %.2f | Min: %.2f | Max: %.2f\n",
           baseline.mean, baseline.std, baseline.min, baseline.max);

    printf("\nEnter number of monitoring cycles: ");
    scanf("%d", &cycles);

    for (int i = 1; i <= cycles; i++) {
        printf("\n--- Monitoring Cycle %d ---\n", i);
        collectData(data, n);
        Stats current = calculateStats(data, n);
        checkDrift(baseline, current, &summary);
    }

    showSummary(summary);
    return 0;
}

/* ---------- FUNCTIONS ---------- */

void collectData(double data[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%lf", &data[i]);
    }
}

Stats calculateStats(double data[], int n) {
    Stats s;
    double sum = 0.0;
    s.min = data[0];
    s.max = data[0];

    for (int i = 0; i < n; i++) {
        sum += data[i];
        if (data[i] < s.min) s.min = data[i];
        if (data[i] > s.max) s.max = data[i];
    }

    s.mean = sum / n;

    double variance = 0.0;
    for (int i = 0; i < n; i++) {
        variance += pow(data[i] - s.mean, 2);
    }

    s.std = sqrt(variance / n);
    return s;
}

double percentChange(double base, double current) {
    if (base == 0) return 0.0;
    return fabs(current - base) / fabs(base) * 100.0;
}

void checkDrift(Stats baseline, Stats current, Summary *summary) {
    summary->totalChecks++;

    double meanDrift = percentChange(baseline.mean, current.mean);
    double stdDrift  = percentChange(baseline.std, current.std);

    printf("Current Mean: %.2f | Std: %.2f\n", current.mean, current.std);
    printf("Mean Drift: %.2f%% | Std Drift: %.2f%%\n", meanDrift, stdDrift);

    double maxDrift = (meanDrift > stdDrift) ? meanDrift : stdDrift;

    if (maxDrift >= HIGH_THRESHOLD) {
        printf("🔴 HIGH DRIFT DETECTED!\n");
        summary->highDrift++;
        logEvent("HIGH", meanDrift, stdDrift);
    }
    else if (maxDrift >= LOW_THRESHOLD) {
        printf("🟡 MEDIUM DRIFT DETECTED\n");
        summary->mediumDrift++;
        logEvent("MEDIUM", meanDrift, stdDrift);
    }
    else {
        printf("🟢 Data Stable (Low Drift)\n");
        summary->lowDrift++;
        logEvent("LOW", meanDrift, stdDrift);
    }
}

void logEvent(const char *severity, double meanDrift, double stdDrift) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (!fp) return;

    time_t now = time(NULL);
    fprintf(fp,
        "[%s] Mean Drift: %.2f%% | Std Drift: %.2f%% | Time: %s",
        severity, meanDrift, stdDrift, ctime(&now));

    fclose(fp);
}

void showSummary(Summary summary) {
    printf("\n=====================================\n");
    printf("        MONITORING SUMMARY\n");
    printf("=====================================\n");
    printf("Total Checks   : %d\n", summary.totalChecks);
    printf("Low Drift      : %d\n", summary.lowDrift);
    printf("Medium Drift   : %d\n", summary.mediumDrift);
    printf("High Drift     : %d\n", summary.highDrift);

    double stability =
        100.0 * (summary.totalChecks - summary.mediumDrift - summary.highDrift)
        / summary.totalChecks;

    printf("Stability Score: %.2f%%\n", stability);
    printf("Log File       : %s\n", LOG_FILE);
}
