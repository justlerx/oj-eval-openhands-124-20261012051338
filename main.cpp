#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Create a vector to track seat occupancy for each segment
    vector<int> occupancy(x, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Check if the order can be satisfied
        bool can_satisfy = true;
        for (int j = u - 1; j < v - 1; j++) {
            if (occupancy[j] + n > k) {
                can_satisfy = false;
                break;
            }
        }
        
        if (can_satisfy) {
            // Update occupancy
            for (int j = u - 1; j < v - 1; j++) {
                occupancy[j] += n;
            }
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}