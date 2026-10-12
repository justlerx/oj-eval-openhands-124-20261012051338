#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Store all active bookings
    vector<pair<int, pair<int, int>>> bookings; // (start, (end, seats))
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Create a vector of all relevant positions
        vector<int> positions;
        positions.push_back(u);
        positions.push_back(v);
        
        // Add all existing booking boundaries
        for (const auto& booking : bookings) {
            positions.push_back(booking.first);
            positions.push_back(booking.second.first);
        }
        
        // Sort and remove duplicates
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());
        
        // Find maximum occupancy in [u, v)
        int max_occupancy = 0;
        
        // Check each segment between consecutive positions in [u, v)
        for (int j = 0; j < (int)positions.size() - 1; j++) {
            int seg_start = positions[j];
            int seg_end = positions[j + 1];
            
            // Skip if segment is outside [u, v)
            if (seg_end <= u || seg_start >= v) continue;
            
            // Calculate occupancy in this segment
            int occupancy = n; // Include the new booking
            for (const auto& booking : bookings) {
                int b_start = booking.first;
                int b_end = booking.second.first;
                int b_seats = booking.second.second;
                
                // If this booking overlaps with the segment
                if (b_start < seg_end && seg_start < b_end) {
                    occupancy += b_seats;
                }
            }
            
            max_occupancy = max(max_occupancy, occupancy);
        }
        
        // Check if we can satisfy this booking
        if (max_occupancy <= k) {
            bookings.emplace_back(u, make_pair(v, n));
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}