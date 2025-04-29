//
// Created by s5614562 on 28/04/25.
//

#ifndef STORAGERECORDTYPES_H
#define STORAGERECORDTYPES_H
#define TypeCode std::array<char, 4>
#include <cstdint>
#include <array>
#include <cstddef>

namespace nsi {
    namespace TypeCodes {
        constexpr TypeCode Header = {'H','E','D','R'};
        constexpr TypeCode Data = {'D','A','T','A'};
    }
    enum class RecordType {
        Header,
        Scene,
        SceneObject,
        Mesh,
        ParticleSystem,
        Material,
        Camera
    };
    enum class RecordSize : size_t {
        Indefinite = 0,
        HeaderSize = sizeof(uint32_t),
    };
    union FourCharCode {
        uint32_t asInt32;
        char asCharCode[4];
    };
    struct recordInfo {
        size_t size;
        [[nodiscard]] bool isIndefinite() const {return size == static_cast<size_t>(RecordSize::Indefinite);}
    };

    recordInfo GetRecordInfo(uint32_t recordType);

}

#endif //STORAGERECORDTYPES_H
