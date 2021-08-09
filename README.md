# ion-hash-cpp
cpp wrapper for amzn ion-c and ion hash cpp implement.

I'm a game developer using unreal engine. I have made a plugin with this cpp project in unreal marketplace. if you are a game developer using unreal engine and want to add qldb to your game. please try my plugin.
https://www.unrealengine.com/marketplace/en-US/product/qldb-with-blueprints-aws

example
```#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "openssl/evp.h"

#include "Ion.h"

/**
 * A QLDB hash is either a 256 bit number or a special empty hash.
 */
class QldbHash {
public:
    static int HASH_SIZE;

    std::vector<unsigned char> _qldbHash;

    /**
     * Creates a QldbHash.
     * @param qldbHash The QLDB hash.
     * @throws RangeError When this hash is not the correct hash size.
     */
    QldbHash(std::vector<unsigned char> qldbHash) {
        if (qldbHash.size() != QldbHash::HASH_SIZE || qldbHash.size() == 0) {
            // throw new RangeError("Hash must be either empty or " + HASH_SIZE + " bytes long.");
            std::cerr << "Hash must be either empty or \" + HASH_SIZE + \" bytes long.";
            return;
        }
        this->_qldbHash = qldbHash;
    }

    /**
     * Sort the current hash value and the hash value provided by `that`, comparing by their **signed** byte values in
     * little-endian order.
     * @param that The Ion hash of the Ion value to compare.
     * @returns An QldbHash object that contains the concatenated hash values.
     */
    QldbHash *dot (QldbHash *that) {
        std::vector<unsigned char> concatenated = QldbHash::_joinHashesPairwise(this->getQldbHash(), that->getQldbHash());

        EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
        EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr);
        EVP_DigestUpdate(mdctx, concatenated.data(), concatenated.size());

        std::vector<unsigned char> newDigest;
        newDigest.resize(EVP_MD_size(EVP_sha256()));
        unsigned int digest_len;
        EVP_DigestFinal_ex(mdctx, newDigest.data(), &digest_len);
        EVP_MD_CTX_destroy(mdctx);

        return new QldbHash(newDigest);
    };

    bool equals (QldbHash *other) {
        return (QldbHash::_hashComparator(this->getQldbHash(), other->getQldbHash()) == 0);
    };

    std::size_t getHashSize () {
        return this->_qldbHash.size();
    };

    std::vector<unsigned char> getQldbHash () {
        return this->_qldbHash;
    };

    bool isEmpty () {
        return (this->_qldbHash.empty());
    };

    /**
     * The QldbHash of an IonValue is just the IonHash of that value.
     * @param value The string or Ion value to be converted to Ion hash.
     * @returns A QldbHash object that contains Ion hash.
     */
    static QldbHash *toQldbHash(std::string value) {
        Ion::Writer writer(false);

        Ion::String str(value);

        writer.writeString(str);

        std::vector<unsigned char> bytes = writer.getBytes();

        return QldbHash::toQldbHash(bytes);
    };

    static QldbHash *toQldbHash(std::vector<unsigned char> value) {
        Ion::Reader reader(value);

        return QldbHash::toQldbHash(reader);
    };

    static QldbHash *toQldbHash(Ion::Reader &reader) {
        reader.next();
        Ion::Value *value = Ion::Value::readAll(reader);

        if (!value) {
            std::cerr << "read Ion value error";
        }

        QldbHash *result = new QldbHash(value->hash());

        return result;
    };

    /**
     * Helper method that concatenates two Uint8Array.
     * @param arrays List of arrays to concatenate, in the order provided.
     * @returns The concatenated array.
     */
    static std::vector<unsigned char> _concatenate (std::vector<unsigned char> h1, std::vector<unsigned char> h2) {
        std::vector<unsigned char> result;
        result.reserve(h1.size() + h2.size());

        result.insert(result.end(), h1.begin(), h1.end());
        result.insert(result.end(), h2.begin(), h2.end());

        return result;
    };

    /**
     * Compares two hashes by their **signed** byte values in little-endian order.
     * @param hash1 The hash value to compare.
     * @param hash2 The hash value to compare.
     * @returns Zero if the hash values are equal, otherwise return the difference of the first pair of non-matching
     *          bytes.
     * @throws RangeError When the hash is not the correct hash size.
     */
    static int _hashComparator (std::vector<unsigned char> hash1, std::vector<unsigned char>hash2) {
        if (hash1.size() != HASH_SIZE || hash2.size() != HASH_SIZE) {
            std::cerr << "Invalid hash.";
            return 0;
        }
        for (int i = hash1.size() - 1; i >= 0; i--) {
            int difference = int((signed char)hash1[i] << 24 >> 24) - int((signed char)hash2[i] << 24 >> 24);
            if (difference != 0) {
                return difference;
            }
        }
        return 0;
    };

    /**
     * Takes two hashes, sorts them, and concatenates them.
     * @param h1 Byte array containing one of the hashes to compare.
     * @param h2 Byte array containing one of the hashes to compare.
     * @returns The concatenated array of hashes.
     */
    static std::vector<unsigned char>_joinHashesPairwise (std::vector<unsigned char> h1, std::vector<unsigned char> h2) {
        if (h1.size() == 0) {
            return h2;
        }
        if (h2.size() == 0) {
            return h1;
        }
        std::vector<unsigned char> concatenated;
        if (QldbHash::_hashComparator(h1, h2) < 0) {
            concatenated = QldbHash::_concatenate(h1, h2);
        }
        else {
            concatenated = QldbHash::_concatenate(h2, h1);
        }
        return concatenated;
    };
};

int QldbHash::HASH_SIZE = 32;

int main() {
    QldbHash *hash = QldbHash::toQldbHash("1e8aUAWHHaO5375HMiArFC");

    return 0;
}```
