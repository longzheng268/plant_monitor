# Install script for directory: E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/AP_TCPServer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "E:/ESP_IDF/Espressif/tools/riscv32-esp-elf/esp-12.2.0_20230208/riscv32-esp-elf/bin/riscv32-esp-elf-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/legacy_or_psa.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "E:/ESP_IDF/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

