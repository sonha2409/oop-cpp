/**
 * ShoppingCartManager.h
 * =====================
 * Singleton Pattern: Single global point of access for the shopping cart.
 *
 * DESIGN:
 * - Only one ShoppingCartManager instance exists. getInstance() returns a reference
 *   to that instance. Constructor is private (or protected) so no one can create
 *   another instance.
 * - The manager holds: list of items (Product*), current shipping strategy,
 *   and provides add/remove, subtotal, total (subtotal + shipping), and optional
 *   order weight for shipping calculation.
 *
 * ANTI-PATTERN: Do not overuse singleton. Use it only when "one cart per session"
 * is a real requirement. For testing, consider a way to reset or inject a mock
 * (e.g., resetInstance() for tests only).
 *
 * STUDENT TASK: Implement ShoppingCartManager.cpp. Ensure thread-safe singleton
 * if you extend to multi-threaded (e.g., C++11 static local).
 */

#ifndef SHOPPING_CART_MANAGER_H
#define SHOPPING_CART_MANAGER_H

#include "Product.h"
#include "ShippingStrategy.h"
#include <memory>
#include <vector>

/**
 * ShoppingCartManager (Singleton)
 * --------------------------------
 * Manages the single application shopping cart: items (Product*), shipping strategy,
 * and totals. Use getInstance() to obtain the unique instance.
 */
class ShoppingCartManager {
public:
    /**
     * getInstance
     * ------------
     * Returns the single instance of ShoppingCartManager. First call constructs
     * the instance; subsequent calls return the same reference. In C++11, you
     * can use a function-local static for thread-safe one-time construction.
     *
     * @return Reference to the singleton ShoppingCartManager.
     */
    static ShoppingCartManager& getInstance();

    /**
     * Prevent copying and assignment (singleton must be unique).
     */
    ShoppingCartManager(const ShoppingCartManager&) = delete;
    ShoppingCartManager& operator=(const ShoppingCartManager&) = delete;

    /**
     * addItem
     * -------
     * Adds one product to the cart. The cart takes ownership of the product
     * (or a clone). If you store Product*, you may clone() so the cart has
     * its own copy; document ownership clearly.
     *
     * @param product Pointer to product to add; can be from ProductFactory.
     *                Manager may store as-is or clone; document in .cpp.
     */
    void addItem(Product* product);

    /**
     * removeItem
     * ----------
     * Removes the item at the given index (0-based). If index is invalid, no-op.
     * Caller is responsible for deleting the Product* if the manager no longer
     * owns it after removal (or manager deletes if it owns; document in .cpp).
     *
     * @param index Index of item to remove (0 <= index < getItemCount()).
     */
    void removeItem(size_t index);

    /**
     * clearCart
     * ---------
     * Removes all items from the cart. If manager owns Product*, delete them here.
     */
    void clearCart();

    /**
     * getItemCount
     * ------------
     * Returns the number of items currently in the cart.
     *
     * @return Number of items (0 if empty).
     */
    size_t getItemCount() const;

    /**
     * getItem
     * -------
     * Returns a pointer to the product at the given index. Do not transfer
     * ownership; the cart still owns the item. Return nullptr if index invalid.
     *
     * @param index 0-based index.
     * @return Product* or nullptr.
     */
    Product* getItem(size_t index);
    const Product* getItem(size_t index) const;

    /**
     * getSubtotal
     * -----------
     * Sum of all item prices (quantity per item can be 1 for simplicity, or
     * extend with quantity). Same currency as Product::getPrice().
     *
     * @return Subtotal >= 0.
     */
    double getSubtotal() const;

    /**
     * setShippingStrategy
     * --------------------
     * Sets the shipping strategy used for calculateTotal() and getShippingCost().
     * Manager may hold a raw pointer or unique_ptr; document ownership. Strategy
     * must outlive the manager or be replaced before destruction.
     *
     * @param strategy Pointer to a shipping strategy (e.g., new StandardShipping()).
     */
    void setShippingStrategy(IShippingStrategy* strategy);

    /**
     * getShippingStrategy
     * --------------------
     * Returns the current shipping strategy (or nullptr if none set).
     * Used for display (name, estimated days) and for calculating cost.
     */
    IShippingStrategy* getShippingStrategy();
    const IShippingStrategy* getShippingStrategy() const;

    /**
     * getShippingCost
     * ----------------
     * Uses the current shipping strategy to compute cost from getSubtotal() and
     * getTotalWeightKg(). Returns 0 if no strategy set.
     *
     * @return Shipping cost >= 0.
     */
    double getShippingCost() const;

    /**
     * getTotal
     * --------
     * getSubtotal() + getShippingCost(). Returns subtotal if no strategy set.
     *
     * @return Total order cost >= 0.
     */
    double getTotal() const;

    /**
     * getTotalWeightKg
     * -----------------
     * Returns the total weight of the cart in kg for shipping calculation.
     * If Product does not have weight, use a default (e.g., 0.5 kg per item) or
     * extend Product with getWeightKg(). Document your assumption in .cpp.
     *
     * @return Total weight >= 0.
     */
    double getTotalWeightKg() const;

    /**
     * resetInstance (optional, for testing)
     * -------------------------------------
     * Destroys the singleton instance so the next getInstance() creates a new one.
     * Only use in tests. Not thread-safe unless you add a mutex. You may omit
     * if not needed for the assignment.
     */
    // static void resetInstance();

private:
    ShoppingCartManager();
    ~ShoppingCartManager();

    std::vector<Product*> items_;           // or std::vector<std::unique_ptr<Product>>
    IShippingStrategy* shippingStrategy_;  // non-owning or owning; document in .cpp
};

#endif // SHOPPING_CART_MANAGER_H
