/**
 * ProductFactory.h
 * ================
 * Factory Pattern: Centralized creation of Product objects.
 *
 * DESIGN:
 * - Client code calls createProduct(type, ...) instead of new Book(...) / new Electronics(...).
 * - Adding a new product type: (1) add enum and concrete class, (2) extend createProduct.
 * - The factory is the only place that knows about concrete product constructors.
 *
 * STUDENT TASK: Implement ProductFactory.cpp.
 */

#ifndef PRODUCT_FACTORY_H
#define PRODUCT_FACTORY_H

#include "Product.h"
#include <memory>
#include <string>

/**
 * ProductFactory
 * --------------
 * Creates Product instances based on ProductType (and optionally type-specific parameters).
 * Returns std::unique_ptr<Product> so ownership is clear; caller can convert to raw pointer
 * if needed for legacy containers.
 */
class ProductFactory {
public:
    /**
     * createProduct (by type only — uses default/sample data)
     * -------------------------------------------------------
     * Creates a single product of the given type with built-in default values.
     * Useful for demos and tests. For real catalog, use the parameterized overload.
     *
     * @param type One of BOOK, ELECTRONICS, CLOTHING.
     * @return unique_ptr to a new Product, or nullptr if type is UNKNOWN/invalid.
     */
    static std::unique_ptr<Product> createProduct(ProductType type);

    /**
     * createProduct (by type and parameters)
     * ---------------------------------------
     * Creates a product with the given type and parameters. Parameter format is
     * type-specific (see below). This keeps the factory interface simple while
     * allowing flexible creation.
     *
     * Book:        params = "title|author|price"  (e.g., "C++ Primer|Stanley Lippman|49.99")
     * Electronics: params = "name|price|warrantyMonths"  (e.g., "Mouse|29.99|24")
     * Clothing:    params = "name|size|price"  (e.g., "T-Shirt|M|19.99")
     *
     * @param type   Product type.
     * @param params Pipe-separated string of values in the order above.
     * @return unique_ptr to a new Product, or nullptr if type/params invalid.
     */
    static std::unique_ptr<Product> createProduct(ProductType type, const std::string& params);

    /**
     * parseProductType
     * ----------------
     * Converts a string (e.g., "book", "electronics", "clothing") to ProductType.
     * Comparison can be case-insensitive. Returns UNKNOWN for invalid input.
     *
     * @param typeStr String such as "book", "Book", "ELECTRONICS".
     * @return Corresponding ProductType or UNKNOWN.
     */
    static ProductType parseProductType(const std::string& typeStr);
};

#endif // PRODUCT_FACTORY_H
