// Using a stack can avoid scanning the array multiple times, allowing focus on parts of it recursively.
// Each value will be visited twice at most, so the time complexity is O(n).
// A vector is used to simulate a stack for storing the result, leading to a space complexity of O(n) as well.
// T: O(n)
// S: O(n)
class Solution {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        if (asteroids.size() <= 1) {
            return asteroids;
        }
        
        // Scans the vector from left to right, saving elements into a stack.
        // Whenever a negative value encountered and the top value of the stack is positive,
        // they are reduced to update the top value of the stack.
        // This process is repeated recursively.
        std::vector<int> stack;
        for (int i = 0; i < asteroids.size(); ++i) {
            if (i == 0 || asteroids[i] > 0 || stack.empty() || stack.back() < 0) {
                stack.emplace_back(asteroids[i]);
                continue;
            }

            // With (asteroids[i] < 0) and (stack.back() > 0), recursively reduce them!
            int sum = 0;
            while (!stack.empty() && stack.back() > 0) {
                sum = stack.back() + asteroids[i];
                if (sum > 0) break; // The coming asteroid is exploded.
                else if (sum == 0) {
                    stack.pop_back(); // Both asteroids exploded!
                    break;
                }
                else stack.pop_back(); // The coming asteroid is unstoppable!
            }
            
            // A huge asteroid appears and destroys all the postive asteroids before it.
            // It is then saved into the stack.
            if (sum < 0) stack.emplace_back(asteroids[i]);
        }

        return stack;
    }
};


// Python code
// class Solution:
//     def asteroidCollision(self, asteroids: List[int]) -> List[int]:
//         if len(asteroids) < 1:
//             return asteroids
        
//         stack = []
//         for i, asteroid in enumerate(asteroids):
//             if len(stack) == 0 or asteroid > 0 or stack[-1] < 0:
//                 stack.append(asteroid)
            
//             sum = 0
//             while len(stack) > 0 and stack[-1] > 0:
//                 sum = stack[-1] + asteroid
//                 if sum > 0:
//                     break
//                 elif sum == 0:
//                     stack.pop()
//                     break
//                 else:
//                     stack.pop()
            
//             if sum < 0:
//                 stack.append(asteroid)
        
//         return stack