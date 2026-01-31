# Project 6: E-commerce Application — Design Document

## Overview

This mini e-commerce system demonstrates **four common design patterns** working together. Each pattern solves a specific problem; understanding when and why to use them (and when not to) is the goal.

---

## 1. Design Patterns Used

### 1.1 Factory Pattern — Creating Products

**When to use:**
- You need to create objects whose **exact type** is determined at runtime (e.g., user selects "Book" or "Electronics").
- You want to **centralize** object creation logic so adding new product types doesn’t scatter `new` calls across the codebase.
- Client code should depend on **abstractions** (e.g., `Product*`) rather than concrete classes.

**Why we use it here:**
- The system has multiple product types (Book, Electronics, Clothing). A factory creates the right concrete product based on a type identifier (string or enum), so the rest of the application only works with `Product*` and doesn’t need to know each concrete class.

**Anti-patterns to avoid:**
- **God Factory:** One factory that creates every kind of object in the system. Prefer smaller, focused factories (e.g., `ProductFactory` only for products).
- **Over-engineering:** Using a factory when you have only one concrete type and no foreseeable expansion. Start simple; introduce a factory when you add a second product type.

---

### 1.2 Observer Pattern — Inventory Notifications

**When to use:**
- One object (the **Subject**) must notify **multiple other objects (Observers)** when its state changes, without the subject knowing their concrete types.
- You want **loose coupling**: the inventory doesn’t call specific UI or logging classes; it just notifies whoever registered.

**Why we use it here:**
- When inventory (e.g., stock level) changes, we may need to: send a low-stock alert, update a dashboard, trigger restock, or log the event. The inventory is the single source of truth; observers react to changes. Adding a new reaction (e.g., email notification) means adding a new observer, not changing the inventory class.

**Anti-patterns to avoid:**
- **Leaking observers:** Forgetting to unregister observers when they are destroyed, leading to dangling pointers. Always unregister in destructors or when the observer is no longer valid.
- **Subject doing too much:** The subject should only maintain a list of observers and notify them; it should not contain business logic that belongs in observers.

---

### 1.3 Strategy Pattern — Shipping Methods

**When to use:**
- You have a **family of algorithms** (e.g., standard, express, free shipping) and want to **interchange** them at runtime.
- You want to avoid large `if/switch` chains and make it easy to add new algorithms without modifying existing code (Open/Closed Principle).

**Why we use it here:**
- Shipping cost and delivery time depend on the selected method. Each method is a strategy: `StandardShipping`, `ExpressShipping`, `FreeShipping`. The order or cart holds a pointer/reference to a `ShippingStrategy`; changing the strategy changes behavior without changing the order class.

**Anti-patterns to avoid:**
- **Strategy bloat:** Creating a new strategy class for every tiny variation. Combine similar behavior (e.g., one strategy with parameters) when it makes sense.
- **Context knowing strategy internals:** The context (e.g., Order) should call a generic interface like `calculateCost()`; it should not downcast or depend on concrete strategy types.

---

### 1.4 Singleton — Shopping Cart Manager

**When to use:**
- You need **exactly one** instance of a class that must be globally accessible (e.g., a single shopping cart for the session, a configuration manager, a connection pool).
- That single point of access is part of the domain (e.g., “there is one cart per user/session”).

**Why we use it here:**
- The shopping cart manager represents the one logical cart. All parts of the application (product listing, checkout, inventory) need to access the same cart instance. Singleton provides that single access point.

**Anti-patterns to avoid:**
- **Overuse:** Not everything needs to be a singleton. Avoid using it for “convenience” global access; prefer dependency injection when you can.
- **Hidden dependencies and testing:** Singletons are hard to mock in unit tests. Consider providing a way to inject or reset the instance in tests (e.g., `setInstanceForTesting()`).
- **Thread safety:** In multi-threaded code, the singleton must be constructed in a thread-safe way (e.g., C++11 static local or mutex); the handout assumes single-threaded for simplicity.

---

## 2. How the Pieces Fit Together

```
┌─────────────────────────────────────────────────────────────────┐
│                     E-commerce Application                        │
├─────────────────────────────────────────────────────────────────┤
│  ProductFactory (Factory)     →  Creates Product* (Book, etc.)   │
│  Inventory (Subject)          →  Notifies Observers on change     │
│  ShippingStrategy (Strategy) →  Order uses one strategy for cost  │
│  ShoppingCartManager (Singleton) → Single cart for the app       │
└─────────────────────────────────────────────────────────────────┘
```

- **Cart** holds `Product*` items (created by the factory) and a `ShippingStrategy*`.
- **Inventory** holds products and notifies observers when quantity changes; observers might update UI or trigger restock.
- **Cart manager** is the singleton that the rest of the app uses to add/remove items and compute totals with the selected shipping strategy.

---

## 3. Implementation Notes for Students

1. **Headers only declare;** all pattern behavior (creation, notification, cost calculation, singleton access) must be implemented in `.cpp` files.
2. **Memory:** Use clear ownership. For example: factory returns `Product*` (caller or cart owns it); cart may own `Product*` and `ShippingStrategy*`; observers are typically not owned by the subject (subject only holds non-owning pointers/references).
3. **Const correctness:** Use `const` for getters and for methods that don’t change observable state.
4. **Pattern boundaries:** Keep each pattern focused: Factory only creates products; Observer only notifies; Strategy only computes shipping; Singleton only manages the single instance and cart operations.

---

## 4. Suggested Implementation Order

1. **Product and ProductFactory** — Get one concrete product and the factory working; then add more product types.
2. **ShippingStrategy** — Implement one strategy (e.g., Standard), then Express and Free.
3. **Inventory and Observer** — Implement Inventory as subject, then one observer (e.g., LowStockAlert).
4. **ShoppingCartManager (Singleton)** — Implement singleton and cart logic; integrate products and shipping strategy.
5. **Integration** — Wire factory, inventory, observers, cart, and shipping in a small `main()` or demo.

This order builds from simple (one product, one strategy) to combined behavior (cart using products and shipping, inventory notifying observers).
