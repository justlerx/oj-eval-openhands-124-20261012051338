#include <iostream>
#include <map>

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
        
        // Find maximum occupancy in range [u, v) with the potential new booking
        int max_occupancy = 0;
        int current_occupancy = 0;
        
        // Iterate through events in the relevant range
        auto it = events.lower_bound(u);
        
        // Start from the beginning if no event at or after u
        if (it == events.begin() && u > events.begin()->first) {
            // Sum all events before u to get initial occupancy
            for (auto e = events.begin(); e != events.end() && e->first < u; ++e) {
                current_occupancy += e->second;
            }
        } else if (it != events.begin()) {
            // Sum events from the last event before u
            auto prev = it;
            do {
                --prev;
                current_occupancy += prev->second;
            } while (prev != events.begin() && prev->first >= u);
            if (prev == events.begin()) {
                current_occupancy += prev->second;
            }
        }
        
        // Now sweep through events from u to v-1
        max_occupancy = current_occupancy;
        
        // Add the new booking's effect at position u
        int temp_occupancy = current_occupancy + n;
        max_occupancy = max(max_occupancy, temp_occupancy);
        
        // Process events from u to v-1
        while (it != events.end() && it->first < v) {
            temp_occupancy += it->second;
            max_occupancy = max(max_occupancy, temp_occupancy);
            ++it;
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