#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Use a map to store events: position -> net change in occupancy
    map<int, int> events;
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Create a temporary map with current events in the range [u, v)
        map<int, int> current_events = events;
        
        // Add the potential new booking
        current_events[u] += n;
        current_events[v] -= n;
        
        // Sweep through the events to find maximum occupancy in [u, v)
        int max_occupancy = 0;
        int current_occupancy = 0;
        
        for (const auto& event : current_events) {
            // If we've passed the range of interest, break
            if (event.first >= v) break;
            
            // If we haven't reached the start, continue
            if (event.first < u) {
                current_occupancy += event.second;
                continue;
            }
            
            // We are in the range [u, v)
            current_occupancy += event.second;
            max_occupancy = max(max_occupancy, current_occupancy);
        }
        
        // Check if we can satisfy this booking
        if (max_occupancy <= k) {
            // Update the actual events map
            events[u] += n;
            events[v] -= n;
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}