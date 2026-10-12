#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // Use difference array to track seat changes
    vector<int> diff(x + 1, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Check if this order can be satisfied by calculating maximum occupancy in range [u-1, v-2]
        // We need to reconstruct the current occupancy in this range
        vector<int> current(x, 0);
        // Reconstruct from diff array
        int curr = 0;
        for (int j = 0; j < x; j++) {
            curr += diff[j];
            current[j] = curr;
        }
        
        bool can_satisfy = true;
        for (int j = u - 1; j < v - 1; j++) {
            if (current[j] + n > k) {
                can_satisfy = false;
                break;
            }
        }
        
        if (can_satisfy) {
            // Update difference array
            diff[u - 1] += n;
            diff[v - 1] -= n;
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}