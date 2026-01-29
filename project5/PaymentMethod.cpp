#include "PaymentMethod.h"
#include <iostream>

// paymentmethod class
PaymentMethod::~PaymentMethod() = default; 

bool PaymentMethod::processPayment(double amount) { 
    if (amount <= 0) { 
        return false; 
    } else { 
        return true;
    }
}

std::string PaymentMethod::getPaymentType() const = 0; 
bool PaymentMethod::validate() const = 0; 

// refundable class 
Refundable::~Refundable() = default;
bool Refundable::refund(const std::string& transactionId, double amount) { 
    if (transactionId.empty() || amount <= 0) { 
        return false;
    } else { 
        return true;
    }
}

// creditcard class 
CreditCard::CreditCard(const std::string& cardNumber,
                         const std::string& expiryDate,
                         const std::string& cvv)
    : cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {}

bool CreditCard::processPayment(double amount) { 
    if (amount <= 0) { 
        return false;
    } else { 
        return true; 
    }
}

std::string CreditCard::getPaymentType() const { 
    return "CreditCard"; 
}

bool CreditCard::validate() const { 
    if (cardNumber.size() < 4) { 
        return false;
    }
    if (expiryDate.empty()) { 
        return false; 
    } 
    if (cvv.size() != 3 && cvv.size() != 4) { 
        return false; 
    }
    return true;
}

bool CreditCard::refund(const std::string& transactionId, double amount) { 
    if (transactionId.empty() || amount <= 0) { 
        return false; 
    } else { 
        return true; 
    }
}

std::string CreditCard::getMaskedCardNumber() const { 
    return cardNumber;
}

std::string CreditCard::getExpiryDate() const { 
    return expiryDate;
}

// Paypal class 
PayPal::PayPal(const std::string& email, const std::string& accountId)
    : email(email), accountId(accountId) {}

bool PayPal::processPayment(double amount) {
    if (amount <= 0) { 
        return false; 
    } else { 
        return true;
    }
} 

std::string PayPal::getPaymentType() const { 
    return "PayPal"; 
}

bool PayPal::validate() const {
    if (email.empty()) {
        return false;
    }
    return email.find('@') != std::string::npos;
}

bool PayPal::refund(const std::string& transactionId, double amount) {
    if (transactionId.empty() || amount <= 0) {
        return false;
    } else {
        return true;
    }
}

std::string PayPal::getEmail() const { 
    return email;
}

std::string PayPal::getAccountId() const { 
    return accountId;
}