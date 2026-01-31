# Project 6: E-commerce Application

A mini e-commerce system demonstrating **Factory**, **Observer**, **Strategy**, and **Singleton** design patterns.

## Contents

| Item | Description |
|------|-------------|
| `DESIGN.md` | When/why to use each pattern, anti-patterns, and how pieces fit together |
| `FUNCTION_SPECS.md` | Detailed specification for each function (pre/post conditions, hints) |
| `include/Product.h` | Abstract Product, Book, Electronics, Clothing (Factory pattern) |
| `include/ProductFactory.h` | Factory for creating products by type |
| `include/InventoryObserver.h` | Inventory (Subject), IInventoryObserver, LowStockAlert, RestockNotifier |
| `include/ShippingStrategy.h` | IShippingStrategy, Standard, Express, Free shipping |
| `include/ShoppingCartManager.h` | Singleton cart manager |

## Patterns at a Glance

- **Factory** — `ProductFactory::createProduct(type)` creates the right `Product*` so the rest of the app doesn’t depend on concrete classes.
- **Observer** — `Inventory` notifies registered observers when stock changes; observers (e.g., `LowStockAlert`) react without the inventory knowing their types.
- **Strategy** — Cart/order holds an `IShippingStrategy*`; shipping cost and delivery time come from the strategy (Standard, Express, Free).
- **Singleton** — `ShoppingCartManager::getInstance()` returns the single cart manager used by the whole application.

## Suggested Implementation Order

1. **Product** — Implement `Product` base (destructor, `getCategory()`), then `Book`, `Electronics`, `Clothing`, and `ProductFactory`.
2. **Shipping** — Implement `StandardShipping`, `ExpressShipping`, `FreeShipping` and `IShippingStrategy` interface.
3. **Inventory & Observers** — Implement `Inventory` (register/unregister, setQuantity, notify), then `LowStockAlert` and `RestockNotifier`.
4. **Cart** — Implement `ShoppingCartManager` singleton (getInstance, add/remove items, subtotal, set strategy, shipping cost, total).
5. **Integration** — A small `main()` that uses factory, inventory, observers, cart, and shipping together.

## Build

Create your own `Makefile` or CMakeLists.txt. Compile with `-I include` so that `#include "Product.h"` etc. resolve. Example:

```bash
g++ -std=c++11 -I include -c Product.cpp -o Product.o
# ... link all .o files
```

## Testing

- Unit test each pattern in isolation (e.g., factory creates correct type, observer receives notifications, strategy returns expected cost).
- Integration test: add products from factory to cart, set shipping strategy, change inventory and verify observers are notified.
