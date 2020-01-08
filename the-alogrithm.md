# The Alogrithm

### BFS and minimal routes

**Breadth-first search** \(**BFS**\) is an algorithm for traversing or searching [tree](https://en.wikipedia.org/wiki/Tree_data_structure) or [graph](https://en.wikipedia.org/wiki/Graph_%28data_structure%29) data structures. It starts at the tree root \(or some arbitrary node of a graph, sometimes referred to as a 'search key'\), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.

Here is a general pseudo code used for implementing BFS:

```text
  procedure BFS(G, start_v) is
      let Q be a queue
      label start_v as discovered
      Q.enqueue(start_v)
      while Q is not empty do
          v := Q.dequeue()
          if v is the goal then
              return v
          for all edges from v to w in G.adjacentEdges(v) do
             if w is not labeled as discovered then
                label w as discovered
                 w.parent := v
                 Q.enqueue(w) 
```

The algorithm of this game is not merely dependant to BFS; instead it is only used the return **minimal length between the spider and butterflies.** 

The function `distToClosestButterfly()` is defined and declared based of BFS algorithm. This is also useful when you check the winning status because this function will return `-1` if it can't find any route to butterflies.

Just like normal BFS pseudo code, a queue is needed to implement this algorithm. But this functions uses two pointers on this queue. One for appending to the queue and one for deciding where the current queue is. 

{% hint style="info" %}
The search will be over whenever the queue is finished or a route to butterfly is found.
{% endhint %}

Here is a poor pseudo code I tried to write for the function. \(Of course the function itself is more complete and bug-free.\)

```text
queue = 0 -1 -2 -2 -2 -2...

while (queue is not -2)
 if (queue is not -1)
  if (current node = butterfly):finish 
                                showdistance
  else:
     for (adjancy):
       if (butterfly): finish
                        showdistance + 1;
       elif (not visited): append to queue
                        mark as visited
       if (next queue is -1) append -1 queue
 if (queue is -1): distance + 1
  queue = nextqueue
```

In this, additional numbers `-1` and `-2` are used. `-2` represents the function being empty. `-1` is added to queue as an interval to show distance will be increased.



### Think [Fuzzy](https://en.wikipedia.org/wiki/Fuzzy_mathematics)

We know what adjacency matrix is \(if don't see [here](https://en.wikipedia.org/wiki/Adjacency_matrix)\) and shows if there is an edge between two vertexes by having values of `0` and `1`.

How about if adjacency matrix can have any unsigned integer as its value. What those values represent? Simple, the **value of links to be moved to or to be cut**.

Suppose, instead of calculating one minimal route, calculating all certain routes between butterflies and the spider which have the minimal length. Each time we add weight to all edges in each route. By this, we assign a **gravity** to all the edges.

In game, we have`linkGravity[][]` to store the gravity of each edge.

But we can go even further. How about calculating the minimal routes and add gravity to the routes that has a bigger length. The implementation in this game calculates `minimal`, `minimal+1` and `minimal+2` routes but with different weights.

```text
#define PrimaryWeight 5
#define SecondaryWeight 3
#define TertiaryWeight 1
```

In every turn of the game, the gravity matrix is set to 0 and reevaluated.

{% hint style="info" %}
There is a limit of minimal length in this game due to the messy way I coded this feature. 😅 See more in `gravity.h`
{% endhint %}

If minimal length is 1 then the fuzzy algorithm won't be used because there is a **definite** way to move and cut.

To evaluate the gravity matrix `proc3stepGravity()` function is used.



### Best Cut

While you understand the philosophy the fuzzy thinking about this process, finding best cut is simple. You only need to find the edge with most gravity and cut it to make the graph lighter 😼

For that, `bestCut()` function is used in the code which directly integrates to gravity matrix.

{% hint style="info" %}
For 1-length routes, fuzzy algorithm is not used because we have definite decision there.
{% endhint %}

### Best Move

Best move is a bit trickier when you want to implement fuzzy algorithm. First you need to decide wheater your code is 1-length or not. If not, then you check each adjacencacy of spider-node and select the one with the most gravity.

For that, `bestMove()` function is used in the code which directly integrates to gravity matrix.

{% hint style="info" %}
The difference between `bestMove()` and `bestCut()` is that `bestMove` only consider nodes that are adjacent to spider vertex.
{% endhint %}

