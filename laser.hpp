#define INF 1000000

#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unsigned int span;
typedef int node;

struct edge {
    node n;
    span cross, first_on, off, on;

    edge(node to, span cross, span first_on, span off, span on) : n(to), cross(cross), first_on(first_on), off(off), on(on) {}
};

typedef unordered_map<node, vector<edge>> graph;

void add_node(graph &g, const node &n) {
    g.emplace(n, vector<edge>());
}

void add_arch(graph &g, const node &a, const edge &b) {
    g.find(a)->second.push_back(b);
}

template<typename T>
bool contains(const unordered_set<T> &set, const T &value) {
    return set.find(value) != end(set);
}

template<typename K, typename V>
bool insert_min(unordered_map<K, V> &map, const K &key, const V &value) {
    auto p = map.insert(make_pair(key, value));

    if (p.second)
        return true;

    if (value < p.first->second) {
        map.erase(p.first);
        map.insert(make_pair(key, value));
        return true;
    }

    return false;
}

template<typename K, typename V>
void replace(unordered_map<K, V> &map, const K &key, const V &value) {
    auto it = map.insert(make_pair(key, value));

    if (!it.second) {
        map.erase(it.first);
        map.insert(make_pair(key, value));
    }
}

span possible_wait(const span &t, const edge &e) {
    if (t < e.first_on) {
        return e.first_on - t;
    }

    auto left = (t - e.first_on) % (e.off + e.on);

    if (left <= e.off - e.cross) {
        return 0;
    }

    return e.off - left + e.on;
}

void dijkstra(const graph &g, const node &src, const node &dst, unordered_map<node, span> &times,
              unordered_map<node, node> &parent) {
    priority_queue<pair<span, node>, vector<pair<span, node>>, greater<pair<span, node>>> queue;

    queue.push({0, src});
    times.insert({src, 0});
    times.insert({dst, INF});

    for (; !queue.empty(); queue.pop()) {
        span s = queue.top().first;
        node n = queue.top().second;
        span t = times.find(n)->second;

        if (s > t) continue;

        for (const auto &e : g.find(n)->second) {
            auto wait = possible_wait(t, e);
            auto possible_span = t + e.cross + wait;
            if (insert_min(times, e.n, possible_span)) {
                queue.push(make_pair(times.find(e.n)->second, e.n));
                replace(parent, e.n, n);
            }
        }
    }
}

template<class OutputIterator>
void build_path(const unordered_map<node, node> &parent, const node &dst, OutputIterator out) {
    const auto last = parent.find(dst);
    const auto first = parent.find(0);
    out++ = dst;
    for (auto it = last; it != first; it = parent.find(it->second)) {
        out++ = it->second;
    }
}

void from_stream(graph &g, istream &input, const int nodes, const int edges) {
    for (node n = 0; n < nodes; n++) {
        add_node(g, n);
    }

    for (auto i = 0; i < edges; i++) {
        node a;
        node b;
        span cross;
        span first_on;
        span off;
        span on;

        input >> a >> b >> cross >> first_on >> off >> on;

        if (cross <= off) {
            add_arch(g, a, edge(b, cross, first_on, off, on));
            add_arch(g, b, edge(a, cross, first_on, off, on));
        }
    }

    add_node(g, 0);
}

template<class OutputIterator>
int laser(istream &input, OutputIterator out) {
    int n;
    int m;

    input >> n >> m;
    graph g;
    from_stream(g, input, n, m);
    node dst = n - 1;
    unordered_map<node, span> times;
    unordered_map<node, node> parent;
    dijkstra(g, 0, dst, times, parent);
    const auto fin = times.find(dst);

    if (fin->second <= INF) {
        vector<node> fromNto0;
        build_path(parent, dst, back_inserter(fromNto0));
        reverse_copy(begin(fromNto0), end(fromNto0), out);
        return fin->second;
    }

    return -1;
}