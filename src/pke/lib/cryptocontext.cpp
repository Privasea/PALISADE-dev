// @file cryptocontext.cpp -- Control for encryption operations.
// @author TPOC: contact@palisade-crypto.org
//
// @copyright Copyright (c) 2019, New Jersey Institute of Technology (NJIT))
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution. THIS SOFTWARE IS
// PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "cryptocontext.h"
#include "utils/serial.h"

namespace lbcrypto {

//! BinFHE
template <typename Element>
void CryptoContextImpl<Element>::GenerateBinFHEContext(uint32_t n, uint32_t N,
                                          const NativeInteger &q,
                                          const NativeInteger &Q,
                                          const NativeInteger &qKS,
                                          double std,
                                          uint32_t baseKS, uint32_t baseG,
                                          uint32_t baseR, BINFHEMETHOD method) {
  auto lweparams = std::make_shared<LWECryptoParams>(n, N, q, Q, qKS, std, baseKS);
  m_params =
      std::make_shared<RingGSWCryptoParams>(lweparams, baseG, baseR, method);
}

template <typename Element>
void CryptoContextImpl<Element>::GenerateBinFHEContext(BINFHEPARAMSET set,
                                          BINFHEMETHOD method) {
  shared_ptr<LWECryptoParams> lweparams;
  NativeInteger Q;
  switch (set) {
    case TOY:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 1024),
                                       1024);
      lweparams = std::make_shared<LWECryptoParams>(64, 512, 512, Q, Q, 3.19, 25);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 9, 32, method);
      break;
    case MEDIUM:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(28, 2048),
                                       2048);
      lweparams = std::make_shared<LWECryptoParams>(422, 1024, 1024, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 10, 32, method);
    case STD128_AP:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 2048),
                                       2048);
      lweparams =
          std::make_shared<LWECryptoParams>(512, 1024, 1024, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 9, 32, method);
      break;
    case STD128_APOPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 2048),
                                       2048);
      lweparams =
          std::make_shared<LWECryptoParams>(502, 1024, 1024, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 9, 32, method);
      break;
    case STD128:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 2048),
                                       2048);
      lweparams =
          std::make_shared<LWECryptoParams>(512, 1024, 1024, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 7, 32, method);
      break;
    case STD128_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 2048),
                                       2048);
      lweparams =
          std::make_shared<LWECryptoParams>(502, 1024, 1024, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 7, 32, method);
      break;
    case STD192:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(37, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(1024, 2048, 1024, Q, 1 << 19, 3.19, 28);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 13, 32, method);
      break;
    case STD192_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(37, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(805, 2048, 1024, Q, 1 << 15, 3.19, 1 << 5);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 13, 32, method);
      break;
    case STD256:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(29, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(1024, 2048, 2048, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 8, 46, method);
      break;
    case STD256_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(29, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(990, 2048, 2048, Q, 1 << 14, 3.19, 1 << 7);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 8, 46, method);
      break;
    case STD128Q:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(50, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(1024, 2048, 1024, Q, 1 << 25, 3.19, 32);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 25, 32, method);
      break;
    case STD128Q_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(50, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(585, 2048, 1024, Q, 1 << 15, 3.19, 32);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 25, 32, method);
      break;
    case STD192Q:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(35, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(1024, 2048, 1024, Q, 1 << 17, 3.19, 64);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 12, 32, method);
      break;
    case STD192Q_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(35, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(875, 2048, 1024, Q, 1 << 15, 3.19, 1 << 5);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 12, 32, method);
      break;
    case STD256Q:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(2048, 2048, 2048, Q, 1 << 16, 3.19, 16);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 7, 46, method);
      break;
    case STD256Q_OPT:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(27, 4096),
                                       4096);
      lweparams =
          std::make_shared<LWECryptoParams>(1225, 2048, 1024, Q, 1 << 16, 3.19, 16);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 7, 32, method);
      break;
    case SIGNED_MOD_TEST:
      Q = PreviousPrime<NativeInteger>(FirstPrime<NativeInteger>(28, 2048),
                                       2048);
      lweparams =
          std::make_shared<LWECryptoParams>(512, 1024, 512, Q, Q, 3.19, 25);
      m_params =
          std::make_shared<RingGSWCryptoParams>(lweparams, 1 << 7, 23, method);
      break;
    default:
      std::string errMsg = "ERROR: No such parameter set exists for FHEW.";
      PALISADE_THROW(config_error, errMsg);
  }
}

template <typename Element>
LWEPrivateKey CryptoContextImpl<Element>::KeyGen() const {
  return m_LWEscheme->KeyGen(m_params->GetLWEParams());
}

template <typename Element>
LWEPrivateKey CryptoContextImpl<Element>::KeyGenN() const {
  return m_LWEscheme->KeyGenN(m_params->GetLWEParams());
}

template <typename Element>
LWECiphertext CryptoContextImpl<Element>::Encrypt(ConstLWEPrivateKey sk,
                                     const LWEPlaintext &m,
                                     BINFHEOUTPUT output) const {
  if (output == FRESH) {
    return m_LWEscheme->Encrypt(m_params->GetLWEParams(), sk, m);
  } else {
    auto ct = m_LWEscheme->Encrypt(m_params->GetLWEParams(), sk, m);
    return m_RingGSWscheme->Bootstrap(m_params, m_BTKey, ct, m_LWEscheme);
  }
}

template <typename Element>
void CryptoContextImpl<Element>::Decrypt(ConstLWEPrivateKey sk, ConstLWECiphertext ct,
                            LWEPlaintext *result) const {
  return m_LWEscheme->Decrypt(m_params->GetLWEParams(), sk, ct, result);
}

template <typename Element>
std::shared_ptr<LWESwitchingKey> CryptoContextImpl<Element>::KeySwitchGen(
    ConstLWEPrivateKey sk, ConstLWEPrivateKey skN) const {
  return m_LWEscheme->KeySwitchGen(m_params->GetLWEParams(), sk, skN);
}

template <typename Element>
void CryptoContextImpl<Element>::BTKeyGen(ConstLWEPrivateKey sk) {
  m_BTKey = m_RingGSWscheme->KeyGen(m_params, m_LWEscheme, sk);
  return;
}

template <typename Element>
LWECiphertext CryptoContextImpl<Element>::EvalBinGate(const BINGATE gate,
                                         ConstLWECiphertext ct1,
                                         ConstLWECiphertext ct2) const {
  return m_RingGSWscheme->EvalBinGate(m_params, gate, m_BTKey, ct1, ct2,
                                      m_LWEscheme);
}

template <typename Element>
LWECiphertext CryptoContextImpl<Element>::Bootstrap(ConstLWECiphertext ct1) const {
  return m_RingGSWscheme->Bootstrap(m_params, m_BTKey, ct1, m_LWEscheme);
}

template <typename Element>
LWECiphertext CryptoContextImpl<Element>::EvalNOT(ConstLWECiphertext ct) const {
  return m_RingGSWscheme->EvalNOT(m_params, ct);
}

template <typename Element>
LWECiphertext CryptoContextImpl<Element>::EvalConstant(bool value) const {
  return m_LWEscheme->NoiselessEmbedding(m_params->GetLWEParams(), value);
}

//! BinFHE




// Initialize global config variable
bool SERIALIZE_PRECOMPUTE = true;

template <typename Element>
void CryptoContextImpl<Element>::EvalMultKeyGen(
    const LPPrivateKey<Element> key) {
  if (key == nullptr || Mismatched(key->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Key passed to EvalMultKeyGen were not generated with this "
                   "crypto context");

  LPEvalKey<Element> k = GetEncryptionAlgorithm()->EvalMultKeyGen(key);

  GetAllEvalMultKeys()[k->GetKeyTag()] = {k};
}

template <typename Element>
void CryptoContextImpl<Element>::EvalMultKeysGen(
    const LPPrivateKey<Element> key) {
  if (key == nullptr || Mismatched(key->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Key passed to EvalMultsKeyGen were not generated with this "
                   "crypto context");

  const vector<LPEvalKey<Element>>& evalKeys =
      GetEncryptionAlgorithm()->EvalMultKeysGen(key);

  GetAllEvalMultKeys()[evalKeys[0]->GetKeyTag()] = evalKeys;
}

template <typename Element>
const vector<LPEvalKey<Element>>&
CryptoContextImpl<Element>::GetEvalMultKeyVector(const string& keyID) {
  auto ekv = GetAllEvalMultKeys().find(keyID);
  if (ekv == GetAllEvalMultKeys().end())
    PALISADE_THROW(not_available_error,
                   "You need to use EvalMultKeyGen so that you have an "
                   "EvalMultKey available for this ID");
  return ekv->second;
}

template <typename Element>
std::map<string, std::vector<LPEvalKey<Element>>>&
CryptoContextImpl<Element>::GetAllEvalMultKeys() {
  return evalMultKeyMap();
}

template <typename Element>
void CryptoContextImpl<Element>::ClearEvalMultKeys() {
  GetAllEvalMultKeys().clear();
}

/**
 * ClearEvalMultKeys - flush EvalMultKey cache for a given id
 * @param id
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalMultKeys(const string& id) {
  auto kd = GetAllEvalMultKeys().find(id);
  if (kd != GetAllEvalMultKeys().end()) GetAllEvalMultKeys().erase(kd);
}

/**
 * ClearEvalMultKeys - flush EvalMultKey cache for a given context
 * @param cc
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalMultKeys(
    const CryptoContext<Element> cc) {
  for (auto it = GetAllEvalMultKeys().begin();
       it != GetAllEvalMultKeys().end();) {
    if (it->second[0]->GetCryptoContext() == cc) {
      it = GetAllEvalMultKeys().erase(it);
    } else {
      ++it;
    }
  }
}

template <typename Element>
void CryptoContextImpl<Element>::InsertEvalMultKey(
    const std::vector<LPEvalKey<Element>>& vectorToInsert) {
  GetAllEvalMultKeys()[vectorToInsert[0]->GetKeyTag()] = vectorToInsert;
}

template <typename Element>
void CryptoContextImpl<Element>::EvalSumKeyGen(
    const LPPrivateKey<Element> privateKey,
    const LPPublicKey<Element> publicKey) {
  if (privateKey == nullptr || Mismatched(privateKey->GetCryptoContext())) {
    PALISADE_THROW(config_error,
                   "Private key passed to EvalSumKeyGen were not generated "
                   "with this crypto context");
  }

  if (publicKey != nullptr &&
      privateKey->GetKeyTag() != publicKey->GetKeyTag()) {
    PALISADE_THROW(
        config_error,
        "Public key passed to EvalSumKeyGen does not match private key");
  }

  auto evalKeys =
      GetEncryptionAlgorithm()->EvalSumKeyGen(privateKey, publicKey);

  GetAllEvalSumKeys()[privateKey->GetKeyTag()] = evalKeys;
}

template <typename Element>
shared_ptr<std::map<usint, LPEvalKey<Element>>>
CryptoContextImpl<Element>::EvalSumRowsKeyGen(
    const LPPrivateKey<Element> privateKey,
    const LPPublicKey<Element> publicKey, usint rowSize, usint subringDim) {
  if (privateKey == nullptr || Mismatched(privateKey->GetCryptoContext())) {
    PALISADE_THROW(config_error,
                   "Private key passed to EvalSumKeyGen were not generated "
                   "with this crypto context");
  }

  if (publicKey != nullptr &&
      privateKey->GetKeyTag() != publicKey->GetKeyTag()) {
    PALISADE_THROW(
        config_error,
        "Public key passed to EvalSumKeyGen does not match private key");
  }

  auto evalKeys = GetEncryptionAlgorithm()->EvalSumRowsKeyGen(
      privateKey, publicKey, rowSize, subringDim);

  return evalKeys;
}

template <typename Element>
shared_ptr<std::map<usint, LPEvalKey<Element>>>
CryptoContextImpl<Element>::EvalSumColsKeyGen(
    const LPPrivateKey<Element> privateKey,
    const LPPublicKey<Element> publicKey) {
  if (privateKey == nullptr || Mismatched(privateKey->GetCryptoContext())) {
    PALISADE_THROW(config_error,
                   "Private key passed to EvalSumKeyGen were not generated "
                   "with this crypto context");
  }

  if (publicKey != nullptr &&
      privateKey->GetKeyTag() != publicKey->GetKeyTag()) {
    PALISADE_THROW(
        config_error,
        "Public key passed to EvalSumKeyGen does not match private key");
  }

  auto evalKeys =
      GetEncryptionAlgorithm()->EvalSumColsKeyGen(privateKey, publicKey);

  return evalKeys;
}

template <typename Element>
const std::map<usint, LPEvalKey<Element>>&
CryptoContextImpl<Element>::GetEvalSumKeyMap(const string& keyID) {
  auto ekv = GetAllEvalSumKeys().find(keyID);
  if (ekv == GetAllEvalSumKeys().end())
    PALISADE_THROW(not_available_error,
                   "You need to use EvalSumKeyGen so that you have EvalSumKeys "
                   "available for this ID");
  return *ekv->second;
}

template <typename Element>
std::map<string, shared_ptr<std::map<usint, LPEvalKey<Element>>>>&
CryptoContextImpl<Element>::GetAllEvalSumKeys() {
  return evalSumKeyMap();
}

template <typename Element>
void CryptoContextImpl<Element>::ClearEvalSumKeys() {
  GetAllEvalSumKeys().clear();
}

/**
 * ClearEvalMultKeys - flush EvalMultKey cache for a given id
 * @param id
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalSumKeys(const string& id) {
  auto kd = GetAllEvalSumKeys().find(id);
  if (kd != GetAllEvalSumKeys().end()) GetAllEvalSumKeys().erase(kd);
}

/**
 * ClearEvalMultKeys - flush EvalMultKey cache for a given context
 * @param cc
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalSumKeys(
    const CryptoContext<Element> cc) {
  for (auto it = GetAllEvalSumKeys().begin();
       it != GetAllEvalSumKeys().end();) {
    if (it->second->begin()->second->GetCryptoContext() == cc) {
      it = GetAllEvalSumKeys().erase(it);
    } else {
      ++it;
    }
  }
}

template <typename Element>
void CryptoContextImpl<Element>::InsertEvalSumKey(
    const shared_ptr<std::map<usint, LPEvalKey<Element>>> mapToInsert) {
  // find the tag
  if (!mapToInsert->empty()) {
    auto onekey = mapToInsert->begin();
    GetAllEvalSumKeys()[onekey->second->GetKeyTag()] = mapToInsert;
  }
}

template <typename Element>
void CryptoContextImpl<Element>::EvalAtIndexKeyGen(
    const LPPrivateKey<Element> privateKey,
    const std::vector<int32_t>& indexList,
    const LPPublicKey<Element> publicKey) {
  if (privateKey == nullptr || Mismatched(privateKey->GetCryptoContext())) {
    PALISADE_THROW(config_error,
                   "Private key passed to EvalAtIndexKeyGen were not generated "
                   "with this crypto context");
  }

  if (publicKey != nullptr &&
      privateKey->GetKeyTag() != publicKey->GetKeyTag()) {
    PALISADE_THROW(
        config_error,
        "Public key passed to EvalAtIndexKeyGen does not match private key");
  }

  auto evalKeys = GetEncryptionAlgorithm()->EvalAtIndexKeyGen(
      publicKey, privateKey, indexList);

  evalAutomorphismKeyMap()[privateKey->GetKeyTag()] = evalKeys;
}

template <typename Element>
const std::map<usint, LPEvalKey<Element>>&
CryptoContextImpl<Element>::GetEvalAutomorphismKeyMap(const string& keyID) {
  auto ekv = evalAutomorphismKeyMap().find(keyID);
  if (ekv == evalAutomorphismKeyMap().end())
    PALISADE_THROW(not_available_error,
                   "You need to use EvalAutomorphismKeyGen so that you have "
                   "EvalAutomorphismKeys available for this ID");
  return *ekv->second;
}

template <typename Element>
std::map<string, shared_ptr<std::map<usint, LPEvalKey<Element>>>>&
CryptoContextImpl<Element>::GetAllEvalAutomorphismKeys() {
  return evalAutomorphismKeyMap();
}

template <typename Element>
void CryptoContextImpl<Element>::ClearEvalAutomorphismKeys() {
  evalAutomorphismKeyMap().clear();
}

/**
 * ClearEvalAutomorphismKeys - flush EvalAutomorphismKey cache for a given id
 * @param id
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalAutomorphismKeys(const string& id) {
  auto kd = evalAutomorphismKeyMap().find(id);
  if (kd != evalAutomorphismKeyMap().end()) evalAutomorphismKeyMap().erase(kd);
}

/**
 * ClearEvalAutomorphismKeys - flush EvalAutomorphismKey cache for a given
 * context
 * @param cc
 */
template <typename Element>
void CryptoContextImpl<Element>::ClearEvalAutomorphismKeys(
    const CryptoContext<Element> cc) {
  for (auto it = evalAutomorphismKeyMap().begin();
       it != evalAutomorphismKeyMap().end();) {
    if (it->second->begin()->second->GetCryptoContext() == cc) {
      it = evalAutomorphismKeyMap().erase(it);
    } else {
      ++it;
    }
  }
}

template <typename Element>
void CryptoContextImpl<Element>::InsertEvalAutomorphismKey(
    const shared_ptr<std::map<usint, LPEvalKey<Element>>> mapToInsert) {
  // find the tag
  auto onekey = mapToInsert->begin();
  evalAutomorphismKeyMap()[onekey->second->GetKeyTag()] = mapToInsert;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalSum(
    ConstCiphertext<Element> ciphertext, usint batchSize) const {
  if (ciphertext == nullptr || Mismatched(ciphertext->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalSum was not generated with this "
                   "crypto context");

  auto evalSumKeys =
      CryptoContextImpl<Element>::GetEvalSumKeyMap(ciphertext->GetKeyTag());
  auto rv =
      GetEncryptionAlgorithm()->EvalSum(ciphertext, batchSize, evalSumKeys);
  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalSumRows(
    ConstCiphertext<Element> ciphertext, usint rowSize,
    const std::map<usint, LPEvalKey<Element>>& evalSumKeys,
    usint subringDim) const {
  if (ciphertext == nullptr || Mismatched(ciphertext->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalSum was not generated with this "
                   "crypto context");

  auto rv = GetEncryptionAlgorithm()->EvalSumRows(ciphertext, rowSize,
                                                  evalSumKeys, subringDim);
  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalSumCols(
    ConstCiphertext<Element> ciphertext, usint rowSize,
    const std::map<usint, LPEvalKey<Element>>& evalSumKeysRight) const {
  if (ciphertext == nullptr || Mismatched(ciphertext->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalSum was not generated with this "
                   "crypto context");

  auto evalSumKeys =
      CryptoContextImpl<Element>::GetEvalSumKeyMap(ciphertext->GetKeyTag());

  auto rv = GetEncryptionAlgorithm()->EvalSumCols(
      ciphertext, rowSize, evalSumKeys, evalSumKeysRight);
  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalAtIndex(
    ConstCiphertext<Element> ciphertext, int32_t index) const {
  if (ciphertext == nullptr || Mismatched(ciphertext->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalAtIndex was not generated with "
                   "this crypto context");

  // If the index is zero, no rotation is needed, copy the ciphertext and return
  // This is done after the keyMap so that it is protected if there's not a valid key.
  if (0 == index) {
    auto rv = ciphertext->Clone();    
    return rv;
  }

  auto evalAutomorphismKeys =
      CryptoContextImpl<Element>::GetEvalAutomorphismKeyMap(
          ciphertext->GetKeyTag());
  
  auto rv = GetEncryptionAlgorithm()->EvalAtIndex(ciphertext, index,
                                                  evalAutomorphismKeys);
  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalMerge(
    const vector<Ciphertext<Element>>& ciphertextVector) const {
  if (ciphertextVector[0] == nullptr ||
      Mismatched(ciphertextVector[0]->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalMerge was not generated with "
                   "this crypto context");

  auto evalAutomorphismKeys =
      CryptoContextImpl<Element>::GetEvalAutomorphismKeyMap(
          ciphertextVector[0]->GetKeyTag());

  auto rv = GetEncryptionAlgorithm()->EvalMerge(ciphertextVector,
                                                evalAutomorphismKeys);

  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalInnerProduct(
    ConstCiphertext<Element> ct1, ConstCiphertext<Element> ct2,
    usint batchSize) const {
  if (ct1 == nullptr || ct2 == nullptr ||
      ct1->GetKeyTag() != ct2->GetKeyTag() ||
      Mismatched(ct1->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalInnerProduct was not generated "
                   "with this crypto context");

  auto evalSumKeys =
      CryptoContextImpl<Element>::GetEvalSumKeyMap(ct1->GetKeyTag());
  auto ek = GetEvalMultKeyVector(ct1->GetKeyTag());

  auto rv = GetEncryptionAlgorithm()->EvalInnerProduct(ct1, ct2, batchSize,
                                                       evalSumKeys, ek[0]);
  return rv;
}

template <typename Element>
Ciphertext<Element> CryptoContextImpl<Element>::EvalInnerProduct(
    ConstCiphertext<Element> ct1, ConstPlaintext ct2, usint batchSize) const {
  if (ct1 == nullptr || ct2 == nullptr || Mismatched(ct1->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to EvalInnerProduct was not generated "
                   "with this crypto context");

  auto evalSumKeys =
      CryptoContextImpl<Element>::GetEvalSumKeyMap(ct1->GetKeyTag());

  auto rv = GetEncryptionAlgorithm()->EvalInnerProduct(ct1, ct2, batchSize,
                                                       evalSumKeys);
  return rv;
}

template <typename Element>
Plaintext CryptoContextImpl<Element>::GetPlaintextForDecrypt(
    PlaintextEncodings pte, shared_ptr<ParmType> evp, EncodingParams ep) {
  auto vp = std::make_shared<typename NativePoly::Params>(
      evp->GetCyclotomicOrder(), ep->GetPlaintextModulus(), 1);

  if (pte == CKKSPacked) return PlaintextFactory::MakePlaintext(pte, evp, ep);

  return PlaintextFactory::MakePlaintext(pte, vp, ep);
}

template <typename Element>
DecryptResult CryptoContextImpl<Element>::Decrypt(
    const LPPrivateKey<Element> privateKey, ConstCiphertext<Element> ciphertext,
    Plaintext* plaintext) {
  if (ciphertext == nullptr)
    PALISADE_THROW(config_error, "ciphertext passed to Decrypt is empty");
  if (plaintext == nullptr)
    PALISADE_THROW(config_error, "plaintext passed to Decrypt is empty");
  if (privateKey == nullptr || Mismatched(privateKey->GetCryptoContext()))
    PALISADE_THROW(config_error,
                   "Information passed to Decrypt was not generated with "
                   "this crypto context");

  // determine which type of plaintext that you need to decrypt into
  // Plaintext decrypted =
  // GetPlaintextForDecrypt(ciphertext->GetEncodingType(),
  // this->GetElementParams(), this->GetEncodingParams());
  Plaintext decrypted = GetPlaintextForDecrypt(
      ciphertext->GetEncodingType(), ciphertext->GetElements()[0].GetParams(),
      this->GetEncodingParams());

  DecryptResult result;

  if ((ciphertext->GetEncodingType() == CKKSPacked) &&
      (typeid(Element) != typeid(NativePoly))) {
    result = GetEncryptionAlgorithm()->Decrypt(privateKey, ciphertext,
                                               &decrypted->GetElement<Poly>());
  } else {
    result = GetEncryptionAlgorithm()->Decrypt(
        privateKey, ciphertext, &decrypted->GetElement<NativePoly>());
  }

  if (result.isValid == false) return result;

  if (ciphertext->GetEncodingType() == CKKSPacked) {
    auto decryptedCKKS =
        std::static_pointer_cast<CKKSPackedEncoding>(decrypted);
    decryptedCKKS->SetDepth(ciphertext->GetDepth());
    decryptedCKKS->SetLevel(ciphertext->GetLevel());
    decryptedCKKS->SetScalingFactor(ciphertext->GetScalingFactor());

    const auto cryptoParamsCKKS =
        std::dynamic_pointer_cast<LPCryptoParametersCKKS<DCRTPoly>>(
            this->GetCryptoParameters());

    decryptedCKKS->Decode(ciphertext->GetDepth(),
                          ciphertext->GetScalingFactor(),
                          cryptoParamsCKKS->GetRescalingTechnique());

  } else {
    decrypted->Decode();
  }

  *plaintext = std::move(decrypted);
  return result;
}

template <typename Element>
DecryptResult CryptoContextImpl<Element>::MultipartyDecryptFusion(
    const vector<Ciphertext<Element>>& partialCiphertextVec,
    Plaintext* plaintext) const {
  DecryptResult result;

  // Make sure we're processing ciphertexts.
  size_t last_ciphertext = partialCiphertextVec.size();
  if (last_ciphertext < 1) return result;

  for (size_t i = 0; i < last_ciphertext; i++) {
    if (partialCiphertextVec[i] == nullptr ||
        Mismatched(partialCiphertextVec[i]->GetCryptoContext()))
      PALISADE_THROW(config_error,
                     "A ciphertext passed to MultipartyDecryptFusion was not "
                     "generated with this crypto context");
    if (partialCiphertextVec[i]->GetEncodingType() !=
        partialCiphertextVec[0]->GetEncodingType())
      PALISADE_THROW(type_error,
                     "Ciphertexts passed to MultipartyDecryptFusion have "
                     "mismatched encoding types");
  }

  // determine which type of plaintext that you need to decrypt into
  Plaintext decrypted = GetPlaintextForDecrypt(
      partialCiphertextVec[0]->GetEncodingType(),
      partialCiphertextVec[0]->GetElements()[0].GetParams(),
      this->GetEncodingParams());

  if ((partialCiphertextVec[0]->GetEncodingType() == CKKSPacked) &&
      (typeid(Element) != typeid(NativePoly)))
    result = GetEncryptionAlgorithm()->MultipartyDecryptFusion(
        partialCiphertextVec, &decrypted->GetElement<Poly>());
  else
    result = GetEncryptionAlgorithm()->MultipartyDecryptFusion(
        partialCiphertextVec, &decrypted->GetElement<NativePoly>());

  if (result.isValid == false) return result;

  if (partialCiphertextVec[0]->GetEncodingType() == CKKSPacked) {
    auto decryptedCKKS =
        std::static_pointer_cast<CKKSPackedEncoding>(decrypted);
    const auto cryptoParamsCKKS =
        std::dynamic_pointer_cast<LPCryptoParametersCKKS<DCRTPoly>>(
            this->GetCryptoParameters());
    decryptedCKKS->Decode(partialCiphertextVec[0]->GetDepth(),
                          partialCiphertextVec[0]->GetScalingFactor(),
                          cryptoParamsCKKS->GetRescalingTechnique());
  } else {
    decrypted->Decode();
  }

  *plaintext = std::move(decrypted);

  return result;
}

}  // namespace lbcrypto
