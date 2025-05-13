#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Product {
int id;
char name[50];
int views;
float discount;
int stock;
int max_stock;
float priority;
} Product;
typedef struct AVLNode {
Product product;

13

struct AVLNode* left;
struct AVLNode* right;
int height;
} AVLNode;
// Priority = weighted score based on views, discount, and urgency
float calculate_priority(Product *p) {
return (p->views * 0.5f) + (p->discount * 0.3f) + ((p->max_stock - p->stock) * 0.2f);
}
int height(AVLNode* node) {
return node ? node->height : 0;
}
int max(int a, int b) {
return (a > b) ? a : b;
}
AVLNode* create_node(Product product) {
AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
node->product = product;
node->left = node->right = NULL;
node->height = 1;
return node;
}
AVLNode* right_rotate(AVLNode* y) {
AVLNode* x = y->left;
AVLNode* T2 = x->right;
x->right = y;
y->left = T2;
y->height = max(height(y->left), height(y->right)) + 1;
x->height = max(height(x->left), height(x->right)) + 1;
return x;
}
AVLNode* left_rotate(AVLNode* x) {
AVLNode* y = x->right;
AVLNode* T2 = y->left;
y->left = x;
x->right = T2;
x->height = max(height(x->left), height(x->right)) + 1;
y->height = max(height(y->left), height(y->right)) + 1;
return y;
}
int get_balance(AVLNode* node) {
return node ? height(node->left) - height(node->right) : 0;
}

14

AVLNode* insert(AVLNode* node, Product product) {
if (!node) return create_node(product);
if (product.priority < node->product.priority)
node->left = insert(node->left, product);
else
node->right = insert(node->right, product);
node->height = 1 + max(height(node->left), height(node->right));
int balance = get_balance(node);
if (balance > 1 && product.priority < node->left->product.priority)
return right_rotate(node);
if (balance < -1 && product.priority > node->right->product.priority)
return left_rotate(node);
if (balance > 1 && product.priority > node->left->product.priority) {
node->left = left_rotate(node->left);
return right_rotate(node);
}
if (balance < -1 && product.priority < node->right->product.priority) {
node->right = right_rotate(node->right);
return left_rotate(node);
}
return node;
}
// Traverse tree in reverse in-order to get top N
void get_top_n(AVLNode* root, Product top[], int* count, int n) {
if (!root || *count >= n) return;
get_top_n(root->right, top, count, n);
if (*count < n) {
top[(*count)++] = root->product;
}
get_top_n(root->left, top, count, n);
}
void print_product(Product p) {
printf(" %s (ID: %d) | Views: %d | Discount: %.1f%% | Stock: %d/%d | ⚡Priority:
%.2f\n",
p.name, p.id, p.views, p.discount, p.stock, p.max_stock, p.priority);
}
int main() {
AVLNode* root = NULL;
int num_products;
printf("📢 Enter the number of flash sale products to input: ");

15

scanf("%d", &num_products);
getchar(); // consume newline
for (int i = 0; i < num_products; i++) {
Product p;
p.id = i + 1;
printf("\n📝 Enter details for Product #%d:\n", p.id);
printf("Name: ");
fgets(p.name, sizeof(p.name), stdin);
p.name[strcspn(p.name, "\n")] = '\0'; // remove newline
printf("Views: ");
scanf("%d", &p.views);
printf("Discount (%%): ");
scanf("%f", &p.discount);
printf("Current Stock: ");
scanf("%d", &p.stock);
printf("Maximum Stock: ");
scanf("%d", &p.max_stock);
getchar(); // consume newline
p.priority = calculate_priority(&p);
root = insert(root, p);
}
int top_n;
printf("\n🔝 How many top products do you want to see? ");
scanf("%d", &top_n);
Product top[top_n];
int count = 0;
get_top_n(root, top, &count, top_n);
printf("\n🔥 Top %d Flash Sale Products:\n", top_n);
for (int i = 0; i < count; i++) {
print_product(top[i]);
}
return 0;
}