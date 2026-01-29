/**
 * @file PaymentMethod.h
 * @brief Payment Processing System — Interfaces, implementations, and checkout
 *
 * LEARNING OBJECTIVES — Abstraction & Interfaces
 * -------------------------------------------------
 * 1. Abstract classes vs Interfaces
 *    - PaymentMethod is an abstract base class (interface): it declares pure virtual
 *      functions that every payment type must implement. It defines a contract.
 *    - In C++, we use a class with pure virtual methods (= 0) as an "interface";
 *      the class cannot be instantiated. Concrete classes (CreditCard, PayPal,
 *      CryptoCurrency) implement the interface.
 *
 * 2. Multiple interface implementation
 *    - A class can implement more than one interface. Here, CreditCard and PayPal
 *      implement both PaymentMethod and Refundable. CryptoCurrency implements
 *      only PaymentMethod (no refund interface in this design).
 *
 * 3. When to use abstraction
 *    - The Checkout class does not depend on CreditCard, PayPal, or CryptoCurrency
 *      directly. It depends only on the PaymentMethod interface. So we can add new
 *      payment types (e.g., BankTransfer) without changing Checkout — open/closed
 *      principle and polymorphism.
 *
 * PROJECT TASKS
 * -------------------------------------------------
 * - Implement the PaymentMethod interface (abstract class with pure virtuals).
 * - Implement the Refundable interface (optional second interface for some types).
 * - Implement CreditCard, PayPal, and CryptoCurrency as concrete payment types.
 * - Build a Checkout class that can process any payment type via the PaymentMethod
 *   interface (process any payment without knowing the concrete type).
 *
 * Students: Implement all declared member functions in PaymentMethod.cpp (and/or
 * separate .cpp files). See FUNCTION_SPECIFICATION.md for detailed behavior.
 */

#ifndef PAYMENT_METHOD_H
#define PAYMENT_METHOD_H

#include <string>

// =============================================================================
// INTERFACE: PaymentMethod (Abstract base — "interface" in C++)
// =============================================================================
// Every payment type must: process a payment, report its type, and validate.
// This class cannot be instantiated; only derived classes that implement all
// pure virtual functions can be used.
// =============================================================================

class PaymentMethod {
public:
    /**
     * Virtual destructor. Required when deleting derived objects through
     * a PaymentMethod* so the correct destructor runs.
     */
    virtual ~PaymentMethod() = default;

    /**
     * Process a payment for the given amount.
     * @param amount Amount to charge (must be positive).
     * @return true if payment succeeded, false otherwise (e.g. validation failed).
     */
    virtual bool processPayment(double amount) = 0;

    /**
     * Return a short identifier for this payment type (e.g. "CreditCard", "PayPal").
     * Used by the checkout system for receipts and logging.
     */
    virtual std::string getPaymentType() const = 0;

    /**
     * Validate that the payment method is ready to use (e.g. card number format,
     * account linked, wallet has address). Called before or during processPayment.
     * @return true if valid, false otherwise.
     */
    virtual bool validate() const = 0;
};

// =============================================================================
// INTERFACE: Refundable (Second interface — multiple interface implementation)
// =============================================================================
// Some payment types support refunds. CreditCard and PayPal implement this;
// CryptoCurrency might not (or you can implement it with different rules).
// A class can inherit from PaymentMethod and also implement Refundable.
// =============================================================================

class Refundable {
public:
    virtual ~Refundable() = default;

    /**
     * Process a refund for a previous transaction.
     * @param transactionId Identifier of the original transaction (e.g. "TXN-001").
     * @param amount Amount to refund (positive).
     * @return true if refund was accepted, false otherwise.
     */
    virtual bool refund(const std::string& transactionId, double amount) = 0;
};

// =============================================================================
// CONCRETE: CreditCard (implements PaymentMethod and Refundable)
// =============================================================================
// Stores card number (masked for display), expiry, and CVV. Validates format;
// processPayment simulates charging the card. Supports refunds.
// =============================================================================

class CreditCard : public PaymentMethod, public Refundable {
public:
    /**
     * Constructor. Store card details. You may mask the number when storing
     * (e.g. keep last 4 digits only) for simplicity.
     */
    CreditCard(const std::string& cardNumber,
               const std::string& expiryDate,
               const std::string& cvv);

    bool processPayment(double amount) override;
    std::string getPaymentType() const override;
    bool validate() const override;

    bool refund(const std::string& transactionId, double amount) override;

    std::string getMaskedCardNumber() const;
    std::string getExpiryDate() const;

private:
    std::string cardNumber;   // or store masked only, e.g. "****1234"
    std::string expiryDate;  // e.g. "12/25"
    std::string cvv;
};

// =============================================================================
// CONCRETE: PayPal (implements PaymentMethod and Refundable)
// =============================================================================
// Stores email and optional linked account ID. Validates that email looks valid;
// processPayment simulates PayPal charge. Supports refunds.
// =============================================================================

class PayPal : public PaymentMethod, public Refundable {
public:
    PayPal(const std::string& email, const std::string& accountId = "");

    bool processPayment(double amount) override;
    std::string getPaymentType() const override;
    bool validate() const override;

    bool refund(const std::string& transactionId, double amount) override;

    std::string getEmail() const;
    std::string getAccountId() const;

private:
    std::string email;
    std::string accountId;
};

// =============================================================================
// CONCRETE: CryptoCurrency (implements PaymentMethod only)
// =============================================================================
// Stores wallet address and currency type (e.g. "BTC", "ETH"). Validates address
// format (e.g. non-empty, minimum length). processPayment simulates crypto
// transfer. Does not implement Refundable in this design (or implement with
// "refunds not supported" returning false).
// =============================================================================

class CryptoCurrency : public PaymentMethod {
public:
    CryptoCurrency(const std::string& walletAddress, const std::string& currencyCode = "BTC");

    bool processPayment(double amount) override;
    std::string getPaymentType() const override;
    bool validate() const override;

    std::string getWalletAddress() const;
    std::string getCurrencyCode() const;

private:
    std::string walletAddress;
    std::string currencyCode;
};

// =============================================================================
// CHECKOUT SYSTEM (processes any PaymentMethod)
// =============================================================================
// Holds a cart total. processCheckout(PaymentMethod&) charges the given payment
// type for that amount — without knowing whether it is CreditCard, PayPal, or
// CryptoCurrency. This demonstrates polymorphism and "program to an interface."
// =============================================================================

class Checkout {
public:
    /**
     * Set the total amount to charge (e.g. sum of cart items).
     * @param total Must be positive.
     */
    void setTotal(double total);

    /**
     * Get the current total.
     */
    double getTotal() const;

    /**
     * Process the checkout using the provided payment method.
     * Validates the payment method, then calls processPayment(getTotal()).
     * @param payment Reference to any concrete payment (CreditCard, PayPal, etc.).
     * @return true if payment succeeded, false otherwise.
     */
    bool processCheckout(PaymentMethod& payment);

    /**
     * Optional: generate a simple receipt string (e.g. "Paid 99.99 via CreditCard").
     */
    std::string getReceipt(const PaymentMethod& payment) const;

private:
    double totalAmount = 0.0;
};

#endif // PAYMENT_METHOD_H
