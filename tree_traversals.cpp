#include <boost/test/unit_test.hpp>

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct node
{
   char  character;
   node* left;
   node* right;
};

void print( const node* n )
{
   std::cout << n->character << " ";
}

// root, left, right
// good for making a copy
void preorder( const node* n )
{
   print( n );

   if( n->left )
      preorder( n->left );

   if( n->right )
      preorder( n->right );
}

void preorder_iterative( const node* n )
{
    stack< const node* > s;

    while( s.empty() == false || n != NULL  )
    {
        if( n != NULL )
        {
            s.push( n );

            print( n );

            n = n->left;
        }
        else
        {
            n = s.top();
            s.pop();

            n = n->right;
        }
    }
}

// left, root, right
// good for accessing nodes in order!
void inorder( const node* n )
{
   if( n->left )
      inorder( n->left );

   print( n );

   if( n->right )
      inorder( n->right );
}

// using std::stack to simulate the function call stack
// basic algorithm:
// - traverse tree until stack is empty
// - left nodes must have NULL for left and right
// - branch nodes must have NULL when left or right not available
// - go most left and push all the nodes along the way
//
void inorder_iterative( const node* n )
{
    stack< const node* > s;

    while( s.empty() == false || n != NULL  )
    {
        if( n != NULL )
        {
            s.push( n );

            n = n->left;
        }
        else
        {
            n = s.top();
            s.pop();

            print( n );

            n = n->right;
        }
    }   
}

// left, right, root
// good for deleting nodes
void postorder( const node* n )
{
   if( n->left )
      postorder( n->left );

   if( n->right )
      postorder( n->right );

   print( n );
}

// breadth first
// print in levels
void breadth_first( const node* root )
{
    queue< const node* > q;   

    q.push( root );

    while( q.empty() == false )
    {
        const node* n = q.front();
        q.pop();

        print( n );

        if( n->left != NULL )
        {
            q.push( n->left );
        }

        if( n->right != NULL )
        {
            q.push( n->right );
        }
    }

// Iteration 0:             add F   -- F
// Iteration 1: print(F) -- add B G -- B G
// Iteration 2: print(B) -- add A D -- G A D
// Iteration 3: print(G) -- add I   -- A D I
// Iteration 4: print(A) --         -- D I
// Iteration 5: print(D) -- add C E -- I C E
// Iteration 6: print(I) -- add H   -- C E H
// Iteration 7: print(C) --         -- E H
// Iteration 8: print(E) --         -- H
// Iteration 8: print(H) --         --
}

////////////////////////////////////
// Insertion
////////////////////////////////////
void insert_helper( node* n, char c )
{
    if( c < n->character )
    {
        if( n->left == NULL )
        {
            n->left = new node;
            n->left->character = c;
            n->left->left = NULL;
            n->left->right = NULL;
        }
        else
        {
            insert_helper( n->left, c );
        }
    }
    else
    {
        if( n->right == NULL )
        {
            n->right = new node;
            n->right->character = c;
            n->right->left = NULL;
            n->right->right = NULL;
        }
        else
        {
            insert_helper( n->right, c );
        }
    }
}

void insert( node* root, char c )
{
    if( root == NULL )
    {
        root = new node;
        root->character = c;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        insert_helper( root, c );
    }
}

void insert_iterative( node* root, char c )
{
    if( root == NULL )
    {
        root = new node;
        root->character = c;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        node* n = root;

        while( true )
        {
            if( n->character > c )
            {
                // go left
                if( n->left != NULL )
                {
                    n = n->left;

                    continue;
                }
                else
                {
                    n->left = new node;
                    n->left->character = c;
                    n->left->left = NULL;
                    n->left->right = NULL;

                    break;
                }
            }
            else
            {
                // go right
                if( n->right != NULL )
                {
                    n = n->right;

                    continue;
                }
                else
                {
                    n->right = new node;
                    n->right->character = c;
                    n->right->left = NULL;
                    n->right->right = NULL;

                    break;
                }
                
            }
        }
    }
}


////////////////////////////////////
// clean up
////////////////////////////////////

void clean_up_helper( node* n, node* parent, int direction )
{
    if( n->left != NULL )
        clean_up_helper( n->left, n, 0 );

    if( n->right != NULL )
        clean_up_helper( n->right, n, 1 );

    delete n;

    if( parent != NULL && direction == 0 )
    {
        parent->left = NULL;
    }

    if( parent != NULL && direction == 1 )
    {
        parent->right = NULL;
    }
}

void clean_up( node* root )
{
    if( root == NULL )
    {
        return;
    }

    clean_up_helper( root, NULL, 0 );
}

BOOST_AUTO_TEST_CASE( tree_traversals )
{
    ///////////////////////F//////////////////////////
    //////////////////////////////////////////////////
    //////////////B///////////////////G///////////////
    //////////////////////////////////////////////////
    ///////A//////////D////////////////////I//////////
    //////////////////////////////////////////////////
    /////////////C///////E////////////////////H///////

    node* root = new node;
    root->character = 'F';
    root->left = NULL;
    root->right = NULL;

    insert( root, 'B' );
    insert( root, 'A' );
    insert( root, 'D' );
    insert( root, 'C' );
    insert( root, 'E' );
    insert( root, 'G' );
    insert( root, 'I' );
    insert( root, 'H' );

    node* root_2 = new node;
    root_2->character = 'F';
    root_2->left = NULL;
    root_2->right = NULL;

    insert_iterative( root_2, 'B' );
    insert_iterative( root_2, 'A' );
    insert_iterative( root_2, 'D' );
    insert_iterative( root_2, 'C' );
    insert_iterative( root_2, 'E' );
    insert_iterative( root_2, 'G' );
    insert_iterative( root_2, 'I' );
    insert_iterative( root_2, 'H' );

    std::cout << "preorder:" << std::endl;
    preorder( root_2 );
    std::cout << std::endl;

    std::cout << "preorder (iterative):" << std::endl;
    preorder_iterative( root );
    std::cout << std::endl;

    std::cout << "inorder:" << std::endl;
    inorder( root_2 );
    std::cout << std::endl;

    std::cout << "inorder ( iterative ):" << std::endl;
    inorder_iterative( root );
    std::cout << std::endl;

    std::cout << "postorder:" << std::endl;
    postorder( root );
    std::cout << std::endl;

    std::cout << "breadth first:" << std::endl;
    breadth_first( root );
    std::cout << std::endl;

    clean_up( root   );
    clean_up( root_2 );
}

