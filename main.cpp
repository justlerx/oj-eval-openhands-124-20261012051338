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
    
    // Use a difference array to track seat changes
    vector<int> diff(MAXN + 1, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Check if this order can be satisfied
        bool can_satisfy = true;
        int current = 0;
        
        // Find the maximum occupancy in range [u, v)
        int max_occupancy = 0;
        for (int j = 1; j < v; j++) {
            current += diff[j];
            if (j >= u) {
                if (current + n > k) {
                    can_satisfy = false;
                    break;
                }
                max_occupancy = max(max_occupancy, current + n);
            }
        }
        
        if (can_satisfy) {
            // Update difference array
            diff[u] += n;
            diff[v] -= n;
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}