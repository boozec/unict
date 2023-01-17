#include <fstream>
#include <iostream>

using namespace std;

enum class Color {
    Red,
    Black
};

template <typename H>
class Node {
public:
    Node(Color color, H key, Node<H>* parent = nullptr, Node<H>* left = nullptr, Node<H>* right = nullptr)
        : color_ { color }
        , key_ { key }
        , parent_ { parent }
        , left_ { left }
        , right_ { right }
    {
    }

    const H&
    key() const
    {
        return key_;
    }

    const Color&
    color() const
    {
        return color_;
    }
    Color&
    color()
    {
        return color_;
    }

    const Node<H>*&
    parent() const
    {
        return parent_;
    }
    Node<H>*&
    parent()
    {
        return parent_;
    }

    const Node<H>*&
    grandp() const
    {
        return parent_->parent();
    }
    Node<H>*&
    grandp()
    {
        return parent_->parent();
    }

    const Node<H>*&
    left() const
    {
        return left_;
    }
    Node<H>*&
    left()
    {
        return left_;
    }

    const Node<H>*&
    right() const
    {
        return right_;
    }
    Node<H>*&
    right()
    {
        return right_;
    }

private:
    Color color_;
    H key_;
    Node<H>* parent_ { nullptr };
    Node<H>* left_ { nullptr };
    Node<H>* right_ { nullptr };
};

template <typename H>
class RBtree {
public:
    RBtree(Node<H>* root = nullptr)
        : root_ { root }
    {
    }

    RBtree<H>*
    insert(H key)
    {
        Node<H>* z = new Node<H>(Color::Red, key);

        Node<H>* y = nullptr;
        auto x = root_;

        while (x != nullptr) {
            y = x;
            if (z->key() < x->key())
                x = x->left();
            else
                x = x->right();
        }

        z->parent() = y;

        if (y == nullptr) {
            root_ = z;
        } else if (z->key() < y->key()) {
            y->left() = z;
        } else {
            y->right() = z;
        }

        if (!z->parent()) {
            z->color() = Color::Black;
        } else if (z->parent()->parent()) {
            fixup(z);
        }

        return this;
    }

    Node<H>*
    root()
    {
        return root_;
    }

    void
    printPre(Node<H>* node, ostream& out)
    {
        if (node == nullptr) {
            return;
        }

        out << "(" << node->key() << " " << (node->color() == Color::Red ? 'R' : 'B') << ") ";
        printPre(node->left(), out);
        printPre(node->right(), out);
    }

    void
    printIn(Node<H>* node, ostream& out)
    {
        if (node == nullptr) {
            return;
        }

        printIn(node->left(), out);
        out << "(" << node->key() << " " << (node->color() == Color::Red ? 'R' : 'B') << ") ";
        printIn(node->right(), out);
    }

    void
    printPost(Node<H>* node, ostream& out)
    {
        if (node == nullptr) {
            return;
        }

        printPost(node->left(), out);
        printPost(node->right(), out);
        out << "(" << node->key() << " " << (node->color() == Color::Red ? 'R' : 'B') << ") ";
    }

private:
    Node<H>* root_ { nullptr };

    Node<H>*
    search(H key)
    {
        auto t = this->root();

        while (t != nullptr && key != t->key()) {
            if (key < t->key()) {
                if (t->left()) {
                    t = t->left();
                } else {
                    break;
                }
            } else {
                if (t->right()) {
                    t = t->right();
                } else {
                    break;
                }
            }
        }

        return t;
    }

    void
    fixup(Node<H>* z)
    {
        while (z->parent()->color() == Color::Red) {
            if (z->grandp()->right() == z->parent()) {
                auto y = z->grandp()->left();
                if (y && y->color() == Color::Red) {
                    z->parent()->color() = Color::Black;
                    y->color() = Color::Black;
                    z->grandp()->color() = Color::Red;
                    z = z->grandp();
                } else {
                    if (z == z->parent()->left()) {
                        z = z->parent();
                        rrotate(z);
                    }
                    z->parent()->color() = Color::Black;
                    z->grandp()->color() = Color::Red;
                    lrotate(z->grandp());
                }
            } else {
                auto y = z->grandp()->right();
                if (y && y->color() == Color::Red) {
                    z->parent()->color() = Color::Black;
                    y->color() = Color::Black;
                    z->grandp()->color() = Color::Red;
                    z = z->grandp();
                } else {
                    if (z == z->parent()->right()) {
                        z = z->parent();
                        lrotate(z);
                    }
                    z->parent()->color() = Color::Black;
                    z->grandp()->color() = Color::Red;
                    rrotate(z->grandp());
                }
            }

            if (z == root_)
                break;
        }

        root_->color() = Color::Black;
    }

    void
    lrotate(Node<H>* node)
    {
        auto y = node->right();
        node->right() = y->left();
        if (y->left())
            y->left()->parent() = node;
        y->parent() = node->parent();

        if (!node->parent())
            root_ = y;
        else if (node == node->parent()->left())
            node->parent()->left() = y;
        else
            node->parent()->right() = y;

        y->left() = node;
        node->parent() = y;
    }

    void
    rrotate(Node<H>* node)
    {
        auto y = node->left();
        node->left() = y->right();
        if (y->right())
            y->right()->parent() = node;
        y->parent() = node->parent();

        if (!node->parent())
            root_ = y;
        else if (node == node->parent()->right())
            node->parent()->right() = y;
        else
            node->parent()->left() = y;

        y->right() = node;
        node->parent() = y;
    }
};

int
main(int argc, char** argv)
{
    int n = (argc > 1) ? stoi(argv[1]) : 100;
    string t, print;
    int m;
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    for (int i = 0; i < n; ++i) {
        fin >> t >> m >> print;

        if (t == "int") {
            RBtree<int>* rb = new RBtree<int>();
            int k;
            for (int j = 0; j < m; ++j) {
                fin >> k;
                rb->insert(k);
            }
            if (print == "preorder")
                rb->printPre(rb->root(), fout);
            else if (print == "postorder")
                rb->printPost(rb->root(), fout);
            else if (print == "inorder")
                rb->printIn(rb->root(), fout);
        } else if (t == "double") {
            RBtree<double>* rb = new RBtree<double>();
            double k;
            for (int j = 0; j < m; ++j) {
                fin >> k;
                rb->insert(k);
            }
            if (print == "preorder")
                rb->printPre(rb->root(), fout);
            else if (print == "postorder")
                rb->printPost(rb->root(), fout);
            else if (print == "inorder")
                rb->printIn(rb->root(), fout);
        }
        fout << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
