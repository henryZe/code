def maze_search(maze, sx, sy, ex, ey):
    directs = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    queue = [[sx, sy, [(sx, sy)]]]

    # bfs
    while queue:
        cur = queue.pop(0)
        if (cur[0], cur[1]) == (ex, ey):
            return cur[2]

        for d in directs:
            r, c = cur[0] + d[0], cur[1] + d[1]
            if 0 <= r < len(maze) and 0 <= c < len(maze[0]) and maze[r][c] == 0:
                maze[r][c] = 2
                path = cur[2][:]
                path.append((r, c))
                queue.append([r, c, path])

while True:
    try:
        mn = list(map(int, input().split()))
        r, c = mn[0], mn[1]
        maze = []
        for i in range(r):
            temp = list(map(int, input().split()))
            maze.append(temp)

        res = maze_search(maze, 0, 0, r - 1, c - 1)
        for i in res:
            print("("+str(i[0])+","+str(i[1])+")")

    except EOFError:
        break