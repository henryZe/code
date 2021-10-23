from typing import List
# bool reconstruct(int x[], DistSet D, int N, int left, int right)

class Solution:
    def turnpike(self, distances: List[int]) -> List[int]:
        def check(points: List[int], point: int, distances: List[int]):
            d_cp = distances[:]
            for p in points:
                if p > point:
                    d = p - point
                else:
                    d = point - p

                if d in d_cp:
                    d_cp.remove(d)
                else:
                    return False, None

            return True, d_cp

        def reconstruct(distances: List[int], points: List[int]) -> bool:
            if not distances:
                return True

            max_d = max(distances)
            max_p = max(points)

            for p in [max_d, max_p - max_d]:
                ok, d_cp = check(points, p, distances)
                if ok == True:
                    points.append(p)
                    if reconstruct(d_cp, points):
                        return True
                    points.pop()

            return False

        p = [0]
        distances.sort()
        p.append(distances.pop())
        reconstruct(distances, p)
        p.sort()
        return p

d = [1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10]
p = Solution().turnpike(d)
print(p)