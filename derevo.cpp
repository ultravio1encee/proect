#include "header.h"

Node* getNode(char ch, int freq, Node* left, Node* right) {
    return new Node{ch, freq, left, right};
}

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

Node* buildHuffmanTree(const std::string& text) {
    std::unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // Если в файле только один уникальный символ, создаем фиктивный узел
    if (pq.size() == 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = getNode('\0', 0, nullptr, nullptr); // Фиктивный узел
        return getNode('\0', left->freq + right->freq, left, right);
    }

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        pq.push(getNode('\0', left->freq + right->freq, left, right));
    }

    return pq.top();
}
