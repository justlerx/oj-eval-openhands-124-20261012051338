#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Event structure for sweep line algorithm
struct Event {
    int pos;
    int type; // 0 for start, 1 for end
    int seats;
    
    Event(int p, int t, int s) : pos(p), type(t), seats(s) {}
    
    bool operator<(const Event& other) const {
        if (pos != other.pos) return pos < other.pos;
        return type < other.type; // Process end events before start events at same position
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Store all active bookings
    vector<pair<int, pair<int, int>>> bookings; // (u, (v, n))
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Create events for current state
        vector<Event> events;
        for (const auto& booking : bookings) {
            events.emplace_back(booking.first, 0, booking.second.second);
            events.emplace_back(booking.second.first, 1, booking.second.second);
        }
        
        // Sort events
        sort(events.begin(), events.end());
        
        // Sweep through events to find maximum occupancy in [u, v-1]
        int max_occupancy = 0;
        int current_occupancy = 0;
        
        for (const auto& event : events) {
            // If we've passed the query range, break
            if (event.pos >= v) break;
            
            // If we haven't reached the start of query range, continue
            if (event.pos < u) continue;
            
            // Update occupancy
            if (event.type == 0) { // Start event
                current_occupancy += event.seats;
            } else { // End event
                current_occupancy -= event.seats;
            }
            
            max_occupancy = max(max_occupancy, current_occupancy);
        }
        
        // Check if we can add this booking
        if (max_occupancy + n <= k) {
            bookings.emplace_back(u, make_pair(v, n));
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}