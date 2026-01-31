/**
 * ShippingStrategy.h
 * ===================
 * Strategy Pattern: Interchangeable algorithms for shipping cost and delivery.
 *
 * DESIGN:
 * - IShippingStrategy: interface for computing cost and (optionally) delivery days.
 * - Order/Cart holds a pointer or reference to IShippingStrategy and calls
 *   calculateCost(subtotal, weight) without knowing the concrete strategy.
 * - Concrete strategies: StandardShipping, ExpressShipping, FreeShipping.
 *   Adding a new method (e.g., OvernightShipping) = new class, no change to Order.
 *
 * ANTI-PATTERN: Do not use a giant switch on "shipping type" inside Order.
 * Use the strategy so Order stays open for extension (new strategies) and closed for modification.
 *
 * STUDENT TASK: Implement ShippingStrategy.cpp and each concrete strategy .cpp.
 */

#ifndef SHIPPING_STRATEGY_H
#define SHIPPING_STRATEGY_H

/**
 * IShippingStrategy (Strategy Interface)
 * ---------------------------------------
 * Defines the contract for computing shipping cost and optionally delivery time.
 * The context (e.g., ShoppingCartManager or Order) calls these methods with
 * order subtotal and total weight; it does not know which concrete strategy is used.
 */
class IShippingStrategy {
public:
    virtual ~IShippingStrategy() = default;

    /**
     * calculateCost
     * --------------
     * Computes the shipping cost based on order subtotal and total weight.
     * Rules are strategy-specific (e.g., free over $50, or $5 + $0.50 per kg).
     *
     * @param orderSubtotal Total price of items (before shipping); >= 0.
     * @param totalWeightKg Total weight of order in kilograms; >= 0.
     * @return Shipping cost in same currency as order; >= 0.
     */
    virtual double calculateCost(double orderSubtotal, double totalWeightKg) const = 0;

    /**
     * getEstimatedDays
     * -----------------
     * Returns the estimated delivery time in days (e.g., 5-7 for standard, 1-2 for express).
     * Can return a fixed value per strategy (e.g., 7 for standard, 2 for express, 5 for free).
     *
     * @return Estimated number of days for delivery (>= 0).
     */
    virtual int getEstimatedDays() const = 0;

    /**
     * getStrategyName
     * ----------------
     * Human-readable name for display (e.g., "Standard", "Express", "Free Shipping").
     *
     * @return Strategy name string.
     */
    virtual const char* getStrategyName() const = 0;
};

/**
 * StandardShipping
 * -----------------
 * Typical rules: base fee + per-kg fee (e.g., $5.00 + $0.50 per kg).
 * Estimated days: e.g., 5–7. Implement calculateCost, getEstimatedDays, getStrategyName.
 */
class StandardShipping : public IShippingStrategy {
public:
    /**
     * @param baseFee      Fixed fee in currency units (e.g., 5.0).
     * @param perKgFee     Additional cost per kilogram (e.g., 0.5).
     * @param estimatedDays Default delivery days (e.g., 6).
     */
    StandardShipping(double baseFee = 5.0, double perKgFee = 0.5, int estimatedDays = 6);

    double calculateCost(double orderSubtotal, double totalWeightKg) const override;
    int getEstimatedDays() const override;
    const char* getStrategyName() const override;

private:
    double baseFee_;
    double perKgFee_;
    int estimatedDays_;
};

/**
 * ExpressShipping
 * ----------------
 * Higher cost, faster delivery (e.g., $12 base + $1.50 per kg, 1–2 days).
 * Implement calculateCost, getEstimatedDays, getStrategyName.
 */
class ExpressShipping : public IShippingStrategy {
public:
    /**
     * @param baseFee       Fixed fee (e.g., 12.0).
     * @param perKgFee      Per-kg fee (e.g., 1.5).
     * @param estimatedDays Default delivery days (e.g., 2).
     */
    ExpressShipping(double baseFee = 12.0, double perKgFee = 1.5, int estimatedDays = 2);

    double calculateCost(double orderSubtotal, double totalWeightKg) const override;
    int getEstimatedDays() const override;
    const char* getStrategyName() const override;

private:
    double baseFee_;
    double perKgFee_;
    int estimatedDays_;
};

/**
 * FreeShipping
 * ------------
 * Free over a minimum order (e.g., $50); otherwise a flat fee or zero.
 * Estimated days can be same as standard (e.g., 5–7). Implement the logic
 * you define (e.g., free if subtotal >= minOrder, else $5).
 */
class FreeShipping : public IShippingStrategy {
public:
    /**
     * @param minOrderForFree Subtotal >= this means $0 shipping (e.g., 50.0).
     * @param feeBelowMin     Shipping cost when subtotal < minOrderForFree (e.g., 5.0).
     * @param estimatedDays   Delivery days (e.g., 5).
     */
    FreeShipping(double minOrderForFree = 50.0, double feeBelowMin = 5.0, int estimatedDays = 5);

    double calculateCost(double orderSubtotal, double totalWeightKg) const override;
    int getEstimatedDays() const override;
    const char* getStrategyName() const override;

private:
    double minOrderForFree_;
    double feeBelowMin_;
    int estimatedDays_;
};

#endif // SHIPPING_STRATEGY_H
