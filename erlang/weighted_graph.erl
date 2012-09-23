-module(weighted_graph).
-compile(export_all).
-author({jha, abhinav}).
-compile(export_all).


new() -> gb_trees:empty().
add_edges(Graph, [])-> Graph;
add_edges(Graph, [{Node1, Node2, Weight}|Edges])-> add_edges(add_edge(Graph, {Node1, Node2, Weight}), Edges).
add_edge(Graph, {Node1, Node2, Weight}) ->
    Edges = gb_trees:lookup(Node1, Graph),
    case Edges of
        none -> gb_trees:enter(Node1, [{Node2, Weight}], Graph);
        {value, X} ->
            case lists:member(Node2, X) of
                false ->
                    gb_trees:enter(Node1, [{Node2, Weight}|X], Graph);
                true ->
                    Graph
            end
    end.


print_graph(Graph)->
    lists:foreach(fun(X) -> error_logger:info_msg(" ~p -> ~p ~n", [X, gb_trees:get(X, Graph)]) end, gb_trees:keys(Graph)).


%% dijkstra's
update_distance(Node, [], Distances, InGraph, {A, B}) -> {Distances, A, B};
update_distance(Node, [{V, W}|Nodes], Distances, InGraph, {MinNode, MinValue}) ->
    case lists:member(V, InGraph) of
        false ->
            D = gb_trees:get(Node, Distances),
            NewDistances = case gb_trees:lookup(V, Distances) of
                none ->
                    case MinValue >= (W+D) of
                        true ->
                            MinNode_ = V,
                            MinValue_ = W+D;
                        false->
                            MinNode_ = MinNode,
                            MinValue_ = MinValue
                    end,
                    gb_trees:enter(V, D+W, Distances);
                {value, DV} ->
                    case (DV >= (W + D)) of
                        true ->
                            case MinValue >= W+D of
                                true ->
                                    MinNode_ = V,
                                    MinValue_ = W+D;
                                _ ->
                                    MinNode_ = MinNode,
                                    MinValue_ = MinValue
                            end,
                            gb_trees:enter(V, W+D, Distances);
                        false ->
                            MinNode_ = MinNode,
                            MinValue_ = MinValue,
                            Distances
                    end
            end;
        true ->
            MinNode_ = MinNode,
            MinValue_ = MinValue,
            NewDistances = Distances
    end,
    update_distance(Node, Nodes, NewDistances, InGraph, {MinNode_, MinValue_}).

update_distances(Graph, Node, Distances, InGraph) ->
    case gb_trees:lookup(Node, Graph) of
        none -> {Distances, none, none};
        {value, X} ->
            update_distance(Node, X, Distances, InGraph, {none, infinity})
    end.


shortest_path(Graph, Node1, Node2)->
    Distances = gb_trees:enter(Node1, 0, gb_trees:empty()),
    Parent = gb_trees:enter(Node1, -1, gb_trees:empty()),
    InGraph = [Node1],
    dijkstra(Graph, Node1,Node2,  Distances, Parent, InGraph).

dijkstra(Graph, X, X, _, Parent, _)-> Parent;
dijkstra(Graph, Cur, Dst, Distances, Parent, InGraph) ->
    {D_, MN_, MD_} = update_distances(Graph, Cur, Distances, InGraph),
    case MN_ of
        none -> Parent;
        _ ->
            P_ = gb_trees:enter(MN_, Cur, Parent),
            dijkstra(Graph, MN_, Dst, D_, P_, [MN_|InGraph])
    end.

print_path(Parent, Node1, Node1) -> error_logger:info_msg("~p ", [Node1]);
print_path(Parent, Node1, Node2) ->
    case gb_trees:lookup(Node2, Parent) of
        none -> ok;
        {value, P} ->
            print_path(Parent, Node1, P),
            error_logger:info_msg(" ~p ", [Node2])
    end.

test() ->
    G = weighted_graph:new(),
    G1 = weighted_graph:add_edges(G, [{a,b, 3}, {a,c, 5}, {a,d, 9}, {b, e, 8}, {e,f, 3}, {c, e, 8}, {d,g, 5}]),
    Parent = shortest_path(G1, b, d),
    error_logger:info_msg("The shortest path between ~p and ~p is : ", [b, d]),
    print_path(Parent, b, d).
