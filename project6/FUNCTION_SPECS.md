# Function Specifications — Implementation Guide for Students

Use this document alongside the header files. Each function lists **purpose**, **parameters**, **return value**, **hints**, and **edge cases**.

---

## 1. Product and Concrete Products

### Product (base class)

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `~Product()` | Virtual destructor so derived objects are destroyed correctly. | Empty body in base is fine; derived classes can add cleanup. | N/A |
| `getCategory()` | Default category when derived class doesn’t override. | Return `"General"`. | N/A |
| `getDescription()` | Pure virtual — each derived class returns its own description. | Book: `title + " by " + author`. Electronics: include name (and optionally warranty). Clothing: `name + " (Size " + size + ")"`. | Empty strings: still return something (e.g., "Unknown"). |
| `getPrice()` | Pure virtual — each derived class returns its stored price. | Return `price_` (or equivalent). | Ensure price >= 0 in constructor. |
| `clone()` | Pure virtual — each derived class returns a new copy of itself. | `return new Book(*this);` etc. Caller owns the pointer. | N/A |

### Book

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `Book(title, author, price)` | Store title, author, price. | Use initializer list. | If price < 0, clamp to 0 or document that you assume valid input. |
| `clone()` | Deep copy. | `return new Book(title_, author_, price_);` or copy ctor. | N/A |

### Electronics

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `Electronics(name, price, warrantyMonths)` | Store name, price, warranty. | warrantyMonths 0 = no warranty. | Same as Book for price. |
| `getWarrantyMonths()` | Return `warrantyMonths_`. | Simple getter. | N/A |
| `getDescription()` | Include name; optionally " (X months warranty)". | If warranty 0, you may omit warranty text. | N/A |

### Clothing

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `Clothing(name, size, price)` | Store name, size, price. | Same pattern as Book. | N/A |
| `getSize()` | Return `size_`. | Return by const reference if stored as std::string. | N/A |

---

## 2. ProductFactory

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `parseProductType(typeStr)` | Map string to enum. | Compare case-insensitive: "book", "Book", "BOOK" → BOOK. | Return UNKNOWN for empty or unknown string. |
| `createProduct(type)` | Create one product of given type with default data. | e.g., BOOK → `new Book("Sample Book", "Author", 9.99)`. | Return nullptr for UNKNOWN. |
| `createProduct(type, params)` | Create product from pipe-separated params. | Split by `'|'`. Book: title, author, price. Electronics: name, price, warranty. Clothing: name, size, price. | Invalid count or non-numeric price → return nullptr. Parse price with std::stod; catch exceptions. |

---

## 3. Inventory (Subject)

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `registerObserver(observer)` | Add to `observers_`. | Push back if not already present (optional duplicate check). | observer nullptr: document “undefined behavior” or ignore. |
| `unregisterObserver(observer)` | Remove from `observers_`. | Erase-remove or loop and erase. | No-op if not found. |
| `setQuantity(productId, quantity)` | Set quantity for productId; add if new. | Find item by productId; update quantity. Then call `notifyObservers(productId, newQuantity)`. | quantity < 0: clamp to 0 or reject; document. |
| `getQuantity(productId)` | Return current quantity. | Linear search in items_; return 0 if not found. | N/A |
| `addStock(productId, delta)` | Change quantity by delta. | Find item; quantity += delta; clamp to 0 if needed. Then notify. | Same as setQuantity for negative. |
| `notifyObservers(productId, newQuantity)` | Call `onStockChanged` on each observer. | For (observer : observers_) observer->onStockChanged(...). | Don’t add/remove observers during iteration (or use a copy of the list). |

---

## 4. Observers

### LowStockAlert

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `LowStockAlert(threshold)` | Store threshold; init alertTriggered_ to false. | Simple ctor. | N/A |
| `onStockChanged(productId, newQuantity)` | If newQuantity <= threshold_, “alert” and set alertTriggered_. | “Alert” can be cout, or set a flag. | N/A |
| `wasAlertTriggered()` | Return alertTriggered_. | Optional: add resetAlertTriggered() for tests. | N/A |

### RestockNotifier

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `onStockChanged(productId, newQuantity)` | If newQuantity == 0 (or low), add productId to restock list. | Push to productsToRestock_ (avoid duplicates if desired). | N/A |
| `getProductsToRestock()` | Return copy of productsToRestock_. | Return by value. | N/A |

---

## 5. Shipping Strategies

### IShippingStrategy (interface)

No implementation in .cpp; only concrete classes implement the methods.

### StandardShipping

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `calculateCost(subtotal, weightKg)` | baseFee_ + weightKg * perKgFee_. | Ignore subtotal unless you want to add a rule (e.g., free over $100). | weightKg < 0: treat as 0. |
| `getEstimatedDays()` | Return estimatedDays_. | Stored in ctor. | N/A |
| `getStrategyName()` | Return `"Standard"` (or literal). | Can return static const char[] or std::string; interface says const char*. | N/A |

### ExpressShipping

Same pattern: typically higher baseFee_ and perKgFee_, lower estimatedDays_. Implement like StandardShipping with different constants.

### FreeShipping

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `calculateCost(subtotal, weightKg)` | If subtotal >= minOrderForFree_ return 0; else return feeBelowMin_. | Weight usually ignored. | subtotal < 0: treat as 0. |

---

## 6. ShoppingCartManager (Singleton)

| Function | Purpose | Hints | Edge cases |
|----------|---------|-------|------------|
| `getInstance()` | Return the single instance. | `static ShoppingCartManager instance; return instance;` (C++11 guarantees thread-safe init). Or use a static pointer and create on first use. | N/A |
| Constructor (private) | Initialize empty items_, shippingStrategy_(nullptr). | Default init. | N/A |
| Destructor | Delete owned Product* in items_; delete or leave shippingStrategy_ per your ownership rule. | If you own strategy, delete it. If not, don’t. | N/A |
| `addItem(product)` | Add product to items_. | Either push_back(product) and take ownership, or push_back(product->clone()). Document which. | product nullptr: ignore or assert. |
| `removeItem(index)` | Remove item at index. | If you own Product*, delete it. Erase from vector. | index >= size: no-op (or return bool). |
| `clearCart()` | Remove all items; delete if owned. | Clear vector; delete each pointer if owning. | N/A |
| `getItemCount()` | Return items_.size(). | Trivial. | N/A |
| `getItem(index)` | Return items_[index] or nullptr. | Check index < size first. | Invalid index: return nullptr. |
| `getSubtotal()` | Sum of getPrice() for each item. | Loop over items_; sum += getItem(i)->getPrice(). | Empty cart: 0. |
| `setShippingStrategy(strategy)` | Store strategy (replace previous if any). | If you previously owned a strategy, delete it. Then shippingStrategy_ = strategy. | strategy nullptr: document (ignore or clear). |
| `getShippingStrategy()` | Return current strategy pointer. | Return shippingStrategy_. | N/A |
| `getTotalWeightKg()` | Sum weight for shipping. | If Product has no weight, use default (e.g., 0.5 per item). Document in .cpp. | Empty cart: 0. |
| `getShippingCost()` | strategy->calculateCost(getSubtotal(), getTotalWeightKg()). | If no strategy, return 0. | N/A |
| `getTotal()` | getSubtotal() + getShippingCost(). | One-liner. | N/A |

---

## Ownership Summary (for your .cpp)

- **Product*** in cart: Document “cart owns” (then delete in removeItem/clearCart/destructor) or “cart stores pointer, caller owns” (then don’t delete).
- **ProductFactory**: Returns unique_ptr; caller can release() to get raw pointer for cart.
- **Inventory**: Does not own observers; only stores raw pointers. Observers must unregister in destructor.
- **IShippingStrategy*** in cart: Document “cart owns” (then setShippingStrategy replaces and deletes old) or “caller owns” (then don’t delete).

Implement these in your .cpp files and add unit/integration tests as required by your instructor.
