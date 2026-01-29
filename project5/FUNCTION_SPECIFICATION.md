# Payment Processing System — Function Specification

This document describes how each function and class should behave so you can implement them correctly. Use it together with `PaymentMethod.h`.

---

## Concepts in This Project

| Concept | Where it appears |
|--------|-------------------|
| **Abstract class / Interface** | `PaymentMethod` is an abstract base class: it has pure virtual functions (`= 0`) and cannot be instantiated. It defines a *contract* that all payment types must fulfill. |
| **Multiple interface implementation** | `CreditCard` and `PayPal` inherit from both `PaymentMethod` and `Refundable`. A single class can implement more than one interface in C++ via multiple inheritance. |
| **When to use abstraction** | The `Checkout` class works with `PaymentMethod&` (or `PaymentMethod*`). It does not depend on `CreditCard`, `PayPal`, or `CryptoCurrency` directly. You can add new payment types without changing `Checkout`. |
| **Polymorphism** | When you call `processCheckout(creditCard)`, the correct `processPayment` (CreditCard’s implementation) is invoked through the base reference. |

---

## 1. Interface: `PaymentMethod` (Abstract Base Class)

**Do not instantiate `PaymentMethod` directly.** Only use it as a base class or as a reference/pointer type (e.g. `PaymentMethod&`, `PaymentMethod*`).

### 1.1 Destructor  
`virtual ~PaymentMethod() = default;`

- **Purpose:** Allow derived objects to be deleted safely via `PaymentMethod*`.
- **Behavior:** The header uses `= default`. No implementation needed in .cpp unless you switch to a custom destructor.

---

### 1.2 Pure virtual functions (no implementation in PaymentMethod)

These are **declared** in the interface and **implemented** only in derived classes:

- `virtual bool processPayment(double amount) = 0;`
- `virtual std::string getPaymentType() const = 0;`
- `virtual bool validate() const = 0;`

You do **not** provide a .cpp implementation for `PaymentMethod` for these; they are implemented in `CreditCard`, `PayPal`, and `CryptoCurrency`.

---

## 2. Interface: `Refundable`

Same idea: abstract interface with pure virtual `refund`. Implement only in classes that inherit from `Refundable` (e.g. `CreditCard`, `PayPal`).

### 2.1 `virtual bool refund(const std::string& transactionId, double amount) = 0;`

- **Purpose:** Process a refund for a previous transaction.
- **Behavior:** Implemented in `CreditCard` and `PayPal`. Can validate `transactionId` and `amount` (e.g. amount > 0) and return true/false. No real network call required; simulate success/failure.

---

## 3. Concrete Class: `CreditCard`

**Inheritance:** `class CreditCard : public PaymentMethod, public Refundable`

### 3.1 Constructor  
`CreditCard(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv)`

- **Purpose:** Store card details. You may store the full card number or only a masked version (e.g. "****1234") for simplicity.
- **Behavior:** Initialize `cardNumber`, `expiryDate`, `cvv` from the parameters.

---

### 3.2 `bool validate() const override`

- **Purpose:** Check if the card is ready to use.
- **Behavior:** Return true if, for example: card number has at least 4 digits (or 13–19 for a full number), expiry is non-empty, CVV is 3 or 4 digits. Use simple rules (e.g. length checks); no need for real card validation.

---

### 3.3 `bool processPayment(double amount) override`

- **Purpose:** Simulate charging the card.
- **Behavior:** If `validate()` is false or `amount <= 0`, return false. Otherwise simulate success (e.g. log "Charged amount to card" and return true). No real payment processing.

---

### 3.4 `std::string getPaymentType() const override`

- Return `"CreditCard"`.

---

### 3.5 `bool refund(const std::string& transactionId, double amount) override`

- **Purpose:** Simulate a refund to the card.
- **Behavior:** If `amount <= 0` or `transactionId` is empty, return false. Otherwise simulate success and return true.

---

### 3.6 Getters  
`getMaskedCardNumber()`, `getExpiryDate()`

- **Purpose:** Return a safe representation of the card (e.g. "****1234") and the expiry date.
- **Behavior:** Return the stored masked number (or compute from full number, e.g. last 4 digits) and `expiryDate`.

---

## 4. Concrete Class: `PayPal`

**Inheritance:** `class PayPal : public PaymentMethod, public Refundable`

### 4.1 Constructor  
`PayPal(const std::string& email, const std::string& accountId = "")`

- **Purpose:** Store PayPal email and optional account ID.
- **Behavior:** Initialize `email` and `accountId`. Default `accountId` to empty if not provided.

---

### 4.2 `bool validate() const override`

- **Purpose:** Check if the PayPal account is ready to use.
- **Behavior:** Return true if email is non-empty and contains `'@'` (simple check). Optionally require non-empty `accountId` if you prefer.

---

### 4.3 `bool processPayment(double amount) override`

- **Purpose:** Simulate charging the PayPal account.
- **Behavior:** If `validate()` is false or `amount <= 0`, return false. Otherwise simulate success and return true.

---

### 4.4 `std::string getPaymentType() const override`

- Return `"PayPal"`.

---

### 4.5 `bool refund(const std::string& transactionId, double amount) override`

- **Purpose:** Simulate a PayPal refund.
- **Behavior:** Same idea as CreditCard: basic validation (amount > 0, non-empty transactionId) then return true.

---

### 4.6 Getters  
`getEmail()`, `getAccountId()`

- **Purpose:** Read-only access to PayPal data.
- **Behavior:** Return the corresponding member.

---

## 5. Concrete Class: `CryptoCurrency`

**Inheritance:** `class CryptoCurrency : public PaymentMethod` (does **not** implement `Refundable` in the base design)

### 5.1 Constructor  
`CryptoCurrency(const std::string& walletAddress, const std::string& currencyCode = "BTC")`

- **Purpose:** Store wallet address and currency code (e.g. "BTC", "ETH").
- **Behavior:** Initialize `walletAddress` and `currencyCode`. Default `currencyCode` to `"BTC"` if not provided.

---

### 5.2 `bool validate() const override`

- **Purpose:** Check if the wallet is ready to use.
- **Behavior:** Return true if `walletAddress` is non-empty and has minimum length (e.g. >= 10 characters). Optionally check `currencyCode` is non-empty.

---

### 5.3 `bool processPayment(double amount) override`

- **Purpose:** Simulate a crypto transfer.
- **Behavior:** If `validate()` is false or `amount <= 0`, return false. Otherwise simulate success and return true.

---

### 5.4 `std::string getPaymentType() const override`

- **Behavior:** Return a string that includes the currency, e.g. `"CryptoCurrency(BTC)"` or `"Crypto-BTC"`, so the receipt is clear.

---

### 5.5 Getters  
`getWalletAddress()`, `getCurrencyCode()`

- **Purpose:** Read-only access to crypto data.
- **Behavior:** Return the corresponding member.

---

## 6. Checkout System: `Checkout`

**Purpose:** Hold a total and process payment using **any** `PaymentMethod`. This is where polymorphism shines: the same `processCheckout` works for CreditCard, PayPal, and CryptoCurrency.

### 6.1 `void setTotal(double total)`

- **Purpose:** Set the amount to charge (e.g. cart total).
- **Behavior:** Set `totalAmount` to `total`. You may reject negative values (e.g. set to 0 or leave as-is; document your choice).

---

### 6.2 `double getTotal() const`

- **Purpose:** Return the current total.
- **Behavior:** Return `totalAmount`.

---

### 6.3 `bool processCheckout(PaymentMethod& payment)`

- **Purpose:** Process the checkout with the given payment method.
- **Behavior:**
  1. If `totalAmount <= 0`, return false.
  2. If `payment.validate()` is false, return false.
  3. Call `payment.processPayment(totalAmount)` and return its result.

  This way, **any** concrete payment type (CreditCard, PayPal, CryptoCurrency) can be passed in, and the correct `validate()` and `processPayment()` are called via the reference.

---

### 6.4 `std::string getReceipt(const PaymentMethod& payment) const`

- **Purpose:** Generate a simple receipt string.
- **Behavior:** Return a string such as `"Paid " + std::to_string(totalAmount) + " via " + payment.getPaymentType()`. You can format the number (e.g. 2 decimal places) if you wish.

---

## 7. Implementation Checklist for Students

- [ ] **PaymentMethod:** No .cpp implementation needed for the abstract class (only the interface in the header). Do not instantiate it.
- [ ] **Refundable:** Same — interface only; implement in CreditCard and PayPal.
- [ ] **CreditCard:** Constructor, `validate()`, `processPayment()`, `getPaymentType()`, `refund()`, getters. Optionally mask card number in constructor or getter.
- [ ] **PayPal:** Constructor, `validate()`, `processPayment()`, `getPaymentType()`, `refund()`, getters.
- [ ] **CryptoCurrency:** Constructor, `validate()`, `processPayment()`, `getPaymentType()`, getters. Does not implement `Refundable`.
- [ ] **Checkout:** `setTotal()`, `getTotal()`, `processCheckout(PaymentMethod&)`, `getReceipt()`.
- [ ] **main() or tests:** Create at least one CreditCard, one PayPal, one CryptoCurrency. Create a Checkout, set a total, and call `processCheckout` with each payment type. Print the receipt for each. Optionally test refunds for CreditCard and PayPal (using `Refundable*` or direct call).

---

## 8. Suggested File Layout

- `PaymentMethod.h` — all declarations (provided).
- `PaymentMethod.cpp` or separate files: `CreditCard.cpp`, `PayPal.cpp`, `CryptoCurrency.cpp`, `Checkout.cpp` — your choice. Implement all declared functions.
- `main.cpp` — demo: create payment objects, create Checkout, set total, process with each payment type, print receipts.

---

## 9. Testing Ideas

1. **Polymorphism:** Store different payment objects in a `std::vector<PaymentMethod*>` (or vector of unique_ptr), then loop and call `processCheckout` for each. No need to know the concrete type.
2. **Validation:** Create a CreditCard with invalid data (e.g. empty CVV); `processCheckout` should return false.
3. **Refundable:** Use a `Refundable*` pointer to call `refund()` on CreditCard and PayPal. CryptoCurrency does not implement Refundable, so it cannot be used through a Refundable* (unless you add a separate interface for “refund not supported” and document it).

Good luck with your implementation.
