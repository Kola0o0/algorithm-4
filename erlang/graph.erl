-module(graph).
-compile(export_all).

test() ->
    G = graph:new(),
    G1 = graph:add_edges(G, [{a,b}, {a,c}, {a,d}, {b, e}, {e,f}, {c, e}, {d,g}]),
    graph:bfs(G1, a),
    shortest_path(G1, a, g).

new() -> gb_trees:empty().

add_edges(Graph, [])-> Graph;
add_edges(Graph, [{Node1, Node2}|Edges])-> add_edges(add_edge(Graph, {Node1, Node2}), Edges).
add_edge(Graph, {Node1, Node2}) ->
    Edges = gb_trees:lookup(Node1, Graph),
    case Edges of
        none -> gb_trees:enter(Node1, [Node2], Graph);
        {value, X} ->
            case lists:member(Node2, X) of
                false ->
                    gb_trees:enter(Node1, [Node2|X], Graph);
                true ->
                    Graph
            end
    end.

delete_edge(Graph, Node1, Node2)->
    case gb_trees:lookup(Node1, Graph) of
        none -> ok;
        {value, Edges} -> gb_trees:enter(Node1, lists:delete(Node2, Edges), Graph)
    end.

print_graph(Graph)->
    lists:foreach(fun(X) -> error_logger:info_msg(" ~p -> ~p ~n", [X, gb_trees:get(X, Graph)]) end, gb_trees:keys(Graph)).


%% bfs
process_node(Node)-> error_logger:info_msg("Node ~p discovered ~n", [Node]).

shortest_path(Graph, Node1, Node2) ->
    Parent = bfs(Graph, Node1),
    print_shortest_path(Parent, Node1, Node2).

print_shortest_path(Parent, Node, Node) ->
    error_logger:info_msg("~p ~n", [Node]);

print_shortest_path(Parent, Node1, Node2) ->
    case gb_trees:lookup(Node2, Parent) of
        none -> ok;
        {value, P} ->
            print_shortest_path(Parent, Node1, P),
            error_logger:info_msg("~p ~n", [Node2])
    end.

bfs(Graph, Node) ->
    Processed = gb_trees:empty(),
    Discovered = gb_trees:enter(Node, true, gb_trees:empty()),
    Parent = gb_trees:enter(Node, -1, gb_trees:empty()),
    Queue = [Node],
    bfs_traverse(Graph, Queue, Processed, Discovered, Parent).

bfs_traverse(Graph, [], Processed, Discovered, Parent) -> Parent;
bfs_traverse(Graph, [Node|Queue], Processed, Discovered, Parent) ->
    process_node(Node),
    Edges = gb_trees:lookup(Node, Graph),
    {Q, P, D, Pa} = case Edges of
        none -> { Queue, Processed, Discovered, Parent};
        {value, X} -> visit_neighbours(Graph, Node, Queue, Processed, Discovered, Parent, X)
    end,
    bfs_traverse(Graph, Q, P, D, Pa).


visit_neighbours(Graph, Node, Q, Processed, Discovered, Parent, []) ->
    Processed_ = gb_trees:enter(Node, true, Processed),
    {Q, Processed_, Discovered, Parent};


visit_neighbours(Graph, Node, Queue, Processed, Discovered, Parent, [E|Edges])->
    case gb_trees:lookup(E, Discovered) of
        none ->
            NewQ = lists:reverse([E|lists:reverse(Queue)]),
            Discovered_ = gb_trees:enter(E, true, Discovered),
            Parent_ = gb_trees:enter(E, Node, Parent);
        _ ->
            NewQ = Queue,
            Discovered_ = Discovered,
            Parent_ = Parent
    end,
    visit_neighbours(Graph, Node, NewQ, Processed, Discovered_, Parent_, Edges).


%%%% DFS
dfs(Graph, Node)->
    Discovered = gb_trees:enter(Node, true, gb_trees:empty()),
    Processed = gb_trees:empty(),
    Parent = gb_trees:enter(Node, -1, gb_trees:empty()),
    Start = gb_trees:enter(Node, now(), gb_trees:empty()),
    Stop = gb_trees:empty(),

    error_logger:info_msg("Examining node ~p .~n", [Node]),
    {D, P, Pa, S, St} = dfs_traverse(Graph, Node, Discovered, Processed, Parent, Start, Stop).


traverse_edges(Graph, Node, Discovered, Processed, Parent, Start, Stop, []) ->
    Processed_ = gb_trees:enter(Node, true, Processed),
    Stop_ = gb_trees:enter(Node, now(), Stop),
    {Discovered, Processed_, Parent, Start, Stop_};

traverse_edges(Graph, Node, Discovered, Processed, Parent, Start, Stop, [E|Edges]) ->
    case gb_trees:lookup(E, Discovered) of
        none ->
            error_logger:info_msg("Edge to ~p found.~n", [E]),
            NewDiscovered = gb_trees:enter(E, true, Discovered),
            NewParent = gb_trees:enter(E, Node, Parent),
            NewStart = gb_trees:enter(E, now(), Start);
        {value, true} ->
            NewDiscovered = Discovered,
            NewParent = Parent,
            NewStart = Start
    end,
    {D_, P_, Pa_, S_, St_} = dfs_traverse(Graph, E, NewDiscovered, Processed, NewParent, NewStart, Stop),
    traverse_edges(Graph, Node, D_, P_, Pa_, S_, St_, Edges).

dfs_traverse(Graph, Node, Discovered, Processed, Parent, Start, Stop) ->
    Val = gb_trees:lookup(Node, Graph),
    case Val of
        none ->
            {Discovered, Processed, Parent, Start, Stop};
        {value, Edges} ->
            traverse_edges(Graph, Node, Discovered, Processed, Parent, Start, Stop, Edges)
    end.
