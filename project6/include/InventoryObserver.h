/**
 * InventoryObserver.h
 * ===================
 * Observer Pattern: Inventory (Subject) notifies Observers when stock changes.
 *
 * DESIGN:
 * - IInventoryObserver: interface for any object that wants to react to inventory events.
 * - Inventory: subject that holds product ID + quantity; when quantity changes, it
 *   calls notify() on all registered observers.
 * - Concrete observers: LowStockAlert (warns when below threshold), RestockNotifier
 *   (logs or triggers restock). You can add more (e.g., EmailNotifier) without
 *   changing Inventory.
 *
 * ANTI-PATTERN: Do not put business logic (e.g., "send email") inside Inventory.
 * Keep Inventory dumb: only manage items and notify observers.
 *
 * STUDENT TASK: Implement Inventory.cpp and concrete observer .cpp files.
 */

#ifndef INVENTORY_OBSERVER_H
#define INVENTORY_OBSERVER_H

#include <string>
#include <vector>

/**
 * Forward declaration to avoid circular dependency.
 * Inventory notifies with productId and new quantity.
 */
class Inventory;

/**
 * IInventoryObserver (Observer Interface)
 * ---------------------------------------
 * Any class that wants to react to inventory changes must implement this interface
 * and register with the Inventory subject. When stock changes, Inventory calls
 * onStockChanged() for each registered observer.
 */
class IInventoryObserver {
public:
    virtual ~IInventoryObserver() = default;

    /**
     * onStockChanged
     * ---------------
     * Called by Inventory when the quantity of a product changes (restock, sale, etc.).
     * Implementations might: log, show alert, trigger restock order, update UI.
     *
     * @param productId   Identifier of the product (e.g., SKU or product name).
     * @param newQuantity The quantity after the change (>= 0).
     */
    virtual void onStockChanged(const std::string& productId, int newQuantity) = 0;
};

/**
 * Inventory (Subject)
 * ------------------
 * Maintains product IDs and their quantities. When quantity is updated (e.g., via
 * setQuantity or addStock), it notifies all registered observers. Observers are
 * not owned by Inventory (no delete); unregister before destroying an observer.
 */
class Inventory {
public:
    Inventory();
    ~Inventory();

    /**
     * registerObserver
     * -----------------
     * Adds an observer to the notification list. The same observer can be registered
     * only once (you may check for duplicates to avoid duplicate notifications).
     *
     * @param observer Non-owning pointer; must outlive Inventory or be unregistered first.
     */
    void registerObserver(IInventoryObserver* observer);

    /**
     * unregisterObserver
     * ------------------
     * Removes an observer so it will no longer receive notifications. Call this
     * in the observer's destructor or when the observer is no longer valid.
     *
     * @param observer Pointer to remove; no-op if not found.
     */
    void unregisterObserver(IInventoryObserver* observer);

    /**
     * setQuantity
     * -----------
     * Sets the quantity for a product. If the product is new, it is added; if
     * quantity changes, all observers are notified with productId and newQuantity.
     *
     * @param productId   Product identifier (e.g., "BOOK-001", "Mouse-X").
     * @param quantity    New quantity (>= 0).
     */
    void setQuantity(const std::string& productId, int quantity);

    /**
     * getQuantity
     * -----------
     * Returns the current quantity for the given product. Returns 0 if product
     * is not in inventory.
     *
     * @param productId Product identifier.
     * @return Quantity (>= 0).
     */
    int getQuantity(const std::string& productId) const;

    /**
     * addStock
     * --------
     * Increases quantity for productId by delta. If product not present, treat as 0
     * then add. Notifies observers with the new total quantity.
     *
     * @param productId Product identifier.
     * @param delta     Amount to add (can be negative to reduce stock; clamp to 0 if needed).
     */
    void addStock(const std::string& productId, int delta);

private:
    /**
     * notifyObservers
     * ----------------
     * Internal: iterates over all registered observers and calls onStockChanged(productId, newQuantity).
     * Call this after any change that affects quantity.
     */
    void notifyObservers(const std::string& productId, int newQuantity);

    struct Item {
        std::string productId;
        int quantity;
    };
    std::vector<Item> items_;
    std::vector<IInventoryObserver*> observers_;
};

/**
 * LowStockAlert (Concrete Observer)
 * ---------------------------------
 * When stock for a product falls at or below a threshold, this observer can
 * "alert" (e.g., print to console, set a flag, or later send email). Implement
 * onStockChanged to check newQuantity <= threshold_ and then perform the alert.
 */
class LowStockAlert : public IInventoryObserver {
public:
    /**
     * @param threshold Alert when quantity <= this value.
     */
    explicit LowStockAlert(int threshold);

    void onStockChanged(const std::string& productId, int newQuantity) override;

    /**
     * wasAlertTriggered
     * ------------------
     * Optional: returns true if at least one alert was triggered (useful for tests).
     * You can reset this in your implementation if needed.
     */
    bool wasAlertTriggered() const;

private:
    int threshold_;
    bool alertTriggered_;
};

/**
 * RestockNotifier (Concrete Observer)
 * -----------------------------------
 * Logs or records that a product may need restocking (e.g., when quantity drops
 * to 0 or below a threshold). Implementation can print to cout, write to a file,
 * or add to a "restock list" for later processing.
 */
class RestockNotifier : public IInventoryObserver {
public:
    void onStockChanged(const std::string& productId, int newQuantity) override;

    /**
     * getProductsToRestock
     * ---------------------
     * Optional: returns list of product IDs that have been flagged for restock
     * (e.g., those that hit 0 or a low threshold). Clear or populate in onStockChanged.
     */
    std::vector<std::string> getProductsToRestock() const;

private:
    std::vector<std::string> productsToRestock_;
};

#endif // INVENTORY_OBSERVER_H
