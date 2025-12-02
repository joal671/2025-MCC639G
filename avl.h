#ifndef __AVL_H__
#define __AVL_H__

#include "binarytree.h"


// Nodo AVL
// Insertar con balance
template <typename Traits>
class CAVLNode : public CBinaryTreeNode<typename Traits::T> {
public:
    using value_type = typename Traits::T;
    using Node       = CBinaryTreeNode<value_type>;
protected:
    int m_balanceFactor = 0; // Factor de balance (altura izquierda - altura derecha)
public:
    CAVLNode(const value_type& v) : Node(v), m_balanceFactor(0) {}
};


// Traits para inserción ascendente
// Compatible con foreach y Compatible con recorridos

template <typename T>
struct AVLAscTraits {
    using value_type = T;
    using Node       = CAVLNode<AVLAscTraits<T>>;
    using CompareFn  = less<T>;
};


// Traits para inserción descendente
// También mantiene compatibilidad con iteradores y recorridos,


template <typename T>
struct AVLDescTraits {
    using value_type = T;
    using Node       = CAVLNode<AVLDescTraits<T>>;
    using CompareFn  = greater<T>;
};

// Clase CAVLTree
// Compatible con Write, Read

template <typename Traits>
class CAVLTree : public CBinaryTree<Traits> {
public:
    using Base       = CBinaryTree<Traits>;
    using Node       = typename Traits::Node;
    using value_type = typename Traits::value_type;  
    using CompareFn  = typename Traits::CompareFn;
    using Container  = CAVLTree<Traits>;
    using iterator   = binary_tree_iterator<Container>; // foreach compatible

protected:
   
    Node* internal_insert(value_type& elem,
                          typename Base::Ref ref,
                          Node* pParent, 
                          Node*& rpOrigin) override
    {
        // TODO: insertar nodo manteniendo estructura BST

        // TODO: verificar factor de balance del nodo

        // TODO: realizar rotaciones si es necesario

        return nullptr; // Placeholder
    }

public:
   
    // Constructor por defecto
    // Compatible Write, Read
   
    CAVLTree() : Base() {}
};