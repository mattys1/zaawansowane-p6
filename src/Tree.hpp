#pragma once

#include <ranges>
#include <vector>
#include <algorithm>
#include <memory>

/**
 * @brief Binary search tree implementation, accepting elements of type T
 */
template <typename T>
class Tree {
private:
	struct TreeNode {
		T contents;
		std::unique_ptr<TreeNode> parent;
		std::vector<std::unique_ptr<TreeNode>> children;

		TreeNode(T _contents, const TreeNode* _parent = nullptr, std::initializer_list<TreeNode*> _children = nullptr):
			parent {std::make_unique(_parent)},
			children { _children | std::ranges::transform([](const auto child) {
				return std::make_unique(child);
			}) },
			contents { _contents } {}
	};

	TreeNode* root;

	void recursive_add(const T& element, TreeNode*& node, TreeNode* parentNode = nullptr) {
		if (node == nullptr) {
			node = new TreeNode(element);
			if (parentNode == nullptr) {
				return;
			}
			node->parent = parentNode;
			if (node->contents >= parentNode->contents) {
				parentNode->right = node;
			}
			else {
				parentNode->left = node;
			}
			return;
		}
		if (element >= node->contents) {
			recursive_add(element, node->right, node);
		}
		else {
			recursive_add(element, node->left, node);
		}
	}

	void preorder_traverse_recursive(TreeNode* node, std::vector<TreeNode*>& traversedTrees) const {
		if (node == nullptr) {
			return;
		}
		traversedTrees.push_back(node);
		preorder_traverse_recursive(node->left, traversedTrees);
		preorder_traverse_recursive(node->right, traversedTrees);
	}

	void inorder_traverse_recursive(TreeNode* node, std::vector<TreeNode*>& traversedTrees) const {
		if (node == nullptr) {
			return;
		}
		inorder_traverse_recursive(node->left, traversedTrees);
		traversedTrees.push_back(node);
		inorder_traverse_recursive(node->right, traversedTrees);
	}

	void postorder_traverse_recursive(TreeNode* node, std::vector<TreeNode*>& traversedTrees) const {
		if (node == nullptr) {
			return;
		}
		postorder_traverse_recursive(node->left, traversedTrees);
		postorder_traverse_recursive(node->right, traversedTrees);
		traversedTrees.push_back(node);
	}

public:
	/**
	 * @brief Constructs a BSTTree with an initial element.
	 * @param element The initial element to be stored in the root node.
	 */
	Tree(const T& element) : root{ new TreeNode(element) } {}

	/**
	 * @brief Constructs an empty BSTTree.
	 */
	Tree() : root{ nullptr } {}

	/**
	 * @brief Destructor to clean up dynamically allocated nodes in the tree.
	 */
	~Tree() { delete root; }

	/**
	 * @brief Adds an element to the tree.
	 * @param element The element to insert into the tree.
	 *
	 * This operation is performed recursively.
	 */
	void add(const T& element) {
		recursive_add(element, root);
	}

	/**
	 * @brief Deletes all nodes in the tree, resetting it to an empty state.
	 */
	void delete_tree() {
		delete root;
		root = nullptr;
	}

	/**
	 * @brief Traverse the tree in the preorder direction and return a vector the contents of each node.
	 * @return Preordered vector of the elements of the tree.
	 */
	std::vector<T> traverse_preorder() const {
		std::vector<TreeNode*> traversedTrees;
		preorder_traverse_recursive(root, traversedTrees);
		return traversedTrees | std::ranges::views::transform([](const TreeNode* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
	}

	/**
	 * @brief Traverse the tree in the inorder direction and return a vector the contents of each node.
	 * @return Inordered vector of the elements of the tree.    
	 */
	std::vector<T> traverse_inorder() const {
		std::vector<TreeNode*> traversedTrees;
		inorder_traverse_recursive(root, traversedTrees);
		return traversedTrees | std::ranges::views::transform([](const TreeNode* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
	}

	/**
	 * @brief Traverse the tree in the postorder direction and return a vector the contents of each node.
	 * @return Postordered vector of the elements of the tree.
	 */
	std::vector<T> traverse_postorder() const {
		std::vector<TreeNode*> traversedTrees;
		postorder_traverse_recursive(root, traversedTrees);
		return traversedTrees | std::ranges::views::transform([](const TreeNode* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
	}

	/**
	 * @brief Delete an element of a given value.
	 * @param value The value of the element to be deleted.
	 * 
	 * This does not differentiate between unique elements of the same value.
	 * @return 0 if the element was successfully deleted, -1 if the element was not found.
	 */
	int delete_element(T value) {
		std::vector<TreeNode*> traversedTrees;
		inorder_traverse_recursive(root, traversedTrees);

		auto elementOfValueIterator = std::find_if(traversedTrees.begin(), traversedTrees.end(),
											 [&value](const TreeNode* tree) { return tree->contents == value; });

		if (elementOfValueIterator == traversedTrees.end()) {
			return -1;
		}

		TreeNode* elementOfValue{ *elementOfValueIterator };
		if (elementOfValue->left == nullptr && elementOfValue->right == nullptr) {
			if (elementOfValue->parent != nullptr) {
				if(elementOfValue->parent->left == elementOfValue) {
					elementOfValue->parent->left = nullptr;
				} else {
					elementOfValue->parent->right = nullptr;
				}
			}

			delete elementOfValue;
		} else {
			TreeNode* successor = *std::next(elementOfValueIterator);
			if (successor->parent != nullptr) {
				if (successor->parent->left == successor) {
					successor->parent->left = nullptr;
				}
				else {
					successor->parent->right = nullptr;
				}
			}
			elementOfValue->contents = successor->contents;
			delete successor;
		}

		return 0;
	}


	/**
	* @brief Finds the path to a value in a binary search tree.
	*
	* @tparam T The type of the tree values.
	* @param value The value to find.
	* @return std::vector<T> Path to the value or empty if not found.
	*/
	std::vector<T> find_path(const T& value) {
		std::vector<T> path;
		TreeNode* curr = root;

		while (root != nullptr) {
			path.push_back(curr->contents);

			if (curr->contents == value) {
				return path;
			}
			else if (value < curr->contents) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		return {};
	}

};
