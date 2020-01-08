# The Alogrithm

### BFS and minimal routes

**Breadth-first search** \(**BFS**\) is an algorithm for traversing or searching [tree](https://en.wikipedia.org/wiki/Tree_data_structure) or [graph](https://en.wikipedia.org/wiki/Graph_%28data_structure%29) data structures. It starts at the tree root \(or some arbitrary node of a graph, sometimes referred to as a 'search key'\), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.

Here is a general pseudocode used for implemeting BFS:

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

The algorithm of this game is not merely depadant to BFS; instead it is only used the return **minimal length between the spider and butterflies.** 

The function `distToClosestButterfly()` is defined and declared based of BFS algorithm. This is also useful when you check the winning status because this function will return `-1` if it can't find any route to butterflies.

Just like normal BFS psoudocode, a queue is needed to implement this algorithm. But this functions uses two pointers on this queue. One for appending to the queue and one for deciding where the current queue is. 

{% hint style="info" %}
The search will be over whenever the queue is finished or a route to butterfly is found.
{% endhint %}

Here is a poor pseudocode I tried to write for the function. \(Of course the function itself is more complete and bug-free.\)

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





