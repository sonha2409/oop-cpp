/**
 * Product.h
 * =========
 * Factory Pattern: Abstract product and concrete product types.
 *
 * DESIGN:
 * - Product is the abstract base. All sellable items (Book, Electronics, Clothing)
 *   inherit from Product so the rest of the app can treat them uniformly (e.g.,
 *   cart holds Product*).
 * - ProductFactory creates the correct concrete Product based on a type string/enum.
 *
 * STUDENT TASK: Implement Product.cpp and all concrete product .cpp files.
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

/**
 * ProductType — Used by the factory to decide which concrete product to create.
 * Add new types here when you add new product classes.
 */
enum class ProductType {
    BOOK,
    ELECTRONICS,
    CLOTHING,
    UNKNOWN
};

/**
 * Product (Abstract Base Class)
 * -----------------------------
 * Represents any sellable item in the store. Concrete products (Book, Electronics,
 * Clothing) override getDescription(), getPrice(), and optionally getCategory().
 *
 * Why abstract? The cart and inventory work with Product* only; they don't need
 * to know the concrete type. This allows adding new product kinds without
 * changing cart/inventory code.
 */
class Product {
public:
    virtual ~Product();

    /**
     * getDescription
     * ---------------
     * Returns a human-readable description of this product (e.g., "C++ Primer, 5th Ed").
     * Used for display in cart, receipts, and listings.
     * @return Description string; should not be empty.
     */
    virtual std::string getDescription() const = 0;

    /**
     * getPrice
     * --------
     * Returns the unit price of this product in a fixed currency unit (e.g., dollars).
     * No rounding is specified here; you may use double or int cents.
     * @return Price >= 0.
     */
    virtual double getPrice() const = 0;

    /**
     * getCategory
     * -----------
     * Returns the category name (e.g., "Books", "Electronics"). Useful for
     * filtering and reporting. Default implementation can return "General".
     * @return Category string.
     */
    virtual std::string getCategory() const;

    /**
     * clone
     * -----
     * Creates a deep copy of this product. Useful when the cart or order needs
     * to store a copy rather than the same pointer (e.g., if the catalog product
     * is later removed or changed). Caller owns the returned pointer.
     * @return New Product* with same type and data as this.
     */
    virtual Product* clone() const = 0;
};

/**
 * Book
 * ----
 * Concrete product: a book with title and author.
 * Implement getDescription() (e.g., "Title by Author"), getPrice(), getCategory() ("Books"), and clone().
 */
class Book : public Product {
public:
    /**
     * Constructor.
     * @param title  Book title (e.g., "The C++ Programming Language").
     * @param author Author name.
     * @param price  Unit price (>= 0).
     */
    Book(const std::string& title, const std::string& author, double price);

    std::string getDescription() const override;
    double getPrice() const override;
    std::string getCategory() const override;
    Product* clone() const override;

private:
    std::string title_;
    std::string author_;
    double price_;
};

/**
 * Electronics
 * -----------
 * Concrete product: an electronics item with name and optional warranty months.
 * Implement getDescription(), getPrice(), getCategory() ("Electronics"), and clone().
 */
class Electronics : public Product {
public:
    /**
     * Constructor.
     * @param name    Product name (e.g., "Wireless Mouse").
     * @param price   Unit price (>= 0).
     * @param warrantyMonths Warranty in months; 0 means none.
     */
    Electronics(const std::string& name, double price, int warrantyMonths = 0);

    std::string getDescription() const override;
    double getPrice() const override;
    std::string getCategory() const override;
    Product* clone() const override;

    /** Optional: get warranty in months (0 = no warranty). */
    int getWarrantyMonths() const;

private:
    std::string name_;
    double price_;
    int warrantyMonths_;
};

/**
 * Clothing
 * --------
 * Concrete product: clothing with name, size, and price.
 * Implement getDescription() (e.g., "T-Shirt (Size M)"), getPrice(), getCategory() ("Clothing"), and clone().
 */
class Clothing : public Product {
public:
    /**
     * Constructor.
     * @param name  Item name (e.g., "Cotton T-Shirt").
     * @param size  Size string (e.g., "S", "M", "L", "XL").
     * @param price Unit price (>= 0).
     */
    Clothing(const std::string& name, const std::string& size, double price);

    std::string getDescription() const override;
    double getPrice() const override;
    std::string getCategory() const override;
    Product* clone() const override;

    const std::string& getSize() const;

private:
    std::string name_;
    std::string size_;
    double price_;
};

#endif // PRODUCT_H
