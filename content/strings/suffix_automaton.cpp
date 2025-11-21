/**
 * Author: Gleb Kostylev
 * Description: Builds Aho-Corasick
 * Time: O(nC)
 * Status: ok submission on CF (see examples)
 */

const int C = 26;

struct Node {
    inline static int timer = 0;

    array<Node*, C> nxt{};
    Node* par = nullptr;
    Node* suf = nullptr;

    // for multi-string automaton
    int last_used = -1;
    
    // more fields if you want
    // bool is_terminal = false;
};

Node* root = new Node();

Node* add(Node* a, int ch) {
    Node* b = new Node();
    b->suf = root;
    b->par = a;
    while (a != nullptr) {
        if (a->nxt[ch] == nullptr) {
            a->nxt[ch] = b;
            a = a->suf;
            continue;
        }
        Node* c = a->nxt[ch];
        if (c->par == a) {
            b->suf = c;
            break;
        }
        Node* d = new Node();
        d->suf = c->suf;
        c->suf = d;
        b->suf = d;
        d->par = a;
        d->nxt = c->nxt;
        while (a != nullptr && a->nxt[ch] == c) {
            a->nxt[ch] = d;
            a = a->suf;
        }
        break;
    }
    return b->par->nxt[ch];
}

void visit_subautomaton(Node* v, auto&& cb = []{}) {
    if (v->last_used == Node::timer) {
        return;
    }
    v->last_used = Node::timer;
    cb(v);
    visit_subautomaton(v->par, cb);
    visit_subautomaton(v->suf, cb);
}
