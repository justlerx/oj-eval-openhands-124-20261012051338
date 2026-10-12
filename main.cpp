#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Store active bookings as (start, end, seats)
    vector<tuple<int, int, int>> bookings;
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Check if this booking can be satisfied
        bool can_satisfy = true;
        
        // For each existing booking, check for overlap with [u, v)
        for (const auto& booking : bookings) {
            int start = get<0>(booking);
            int end = get<1>(booking);
            int seats = get<2>(booking);
            
            // Check if there is overlap
            if (u < end && start < v) { // Overlapping intervals
                // The overlap is [max(u, start), min(v, end))
                // This booking would add n seats, and the existing booking has 'seats' seats
                // If n + seats > k, then this booking cannot be satisfied
                if (n + seats > k) {
                    can_satisfy = false;
                    break;
                }
            }
        }
        
        if (can_satisfy) {
            bookings.emplace_back(u, v, n);
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}