/*
 * Copyright 2016-2017 TATA ELXSI
 * Copyright 201-20176 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "cdmi.h"

#include "host/wv_host.h"
#include "scoped_ptr.h"

using namespace std;
using namespace widevine;
using namespace wvcdm;

namespace CDMi
{
class MediaKeySession : public IMediaKeySession
{
public:
    MediaKeySession(Cdm*, int32_t);
    virtual ~MediaKeySession(void);

    virtual void Run(
        const IMediaKeySessionCallback *f_piMediaKeySessionCallback);

    void* RunThread(int i);

    virtual CDMi_RESULT Load();

    virtual void Update(
        const uint8_t *f_pbKeyMessageResponse,
        uint32_t f_cbKeyMessageResponse);

    virtual CDMi_RESULT Remove();

    virtual CDMi_RESULT Close(void);

    virtual const char* GetSessionId(void) const;

    virtual const char* GetKeySystem(void) const;

    CDMi_RESULT Init(
        int32_t licenseType,
        const char *f_pwszInitDataType,
        const uint8_t *f_pbInitData,
        uint32_t f_cbInitData,
        const uint8_t *f_pbCDMData,
        uint32_t f_cbCDMData);

    virtual CDMi_RESULT Decrypt(
        const uint8_t *f_pbSessionKey,
        uint32_t f_cbSessionKey,
        const uint32_t *f_pdwSubSampleMapping,
        uint32_t f_cdwSubSampleMapping,
        const uint8_t *f_pbIV,
        uint32_t f_cbIV,
        const uint8_t *f_pbData,
        uint32_t f_cbData,
        uint32_t *f_pcbOpaqueClearContent,
        uint8_t **f_ppbOpaqueClearContent);

    virtual CDMi_RESULT ReleaseClearContent(
        const uint8_t *f_pbSessionKey,
        uint32_t f_cbSessionKey,
        const uint32_t  f_cbClearContentOpaque,
        uint8_t  *f_pbClearContentOpaque );

    // Callback Interfaces
    virtual void onMessageUrl(const std::string& f_sessionId,
        const std::string& f_serverUrl) {}

    virtual void onMessage(const std::string& f_sessionId,
        Cdm::MessageType f_messageType,
        const std::string& f_message);
  
    virtual void onKeyStatusesChange(const std::string& f_sessionId);
    virtual void onRemoveComplete(const std::string& f_sessionId);

private:
    static void* _CallRunThread(
        void *arg);
    static void* _CallRunThread2(
        void *arg);
    void onKeyStatusError(const std::string& f_sessionId, Cdm::Status status);

private:
    Cdm *m_cdm;
    std::string m_CDMData;
    std::string m_initData;
    Cdm::InitDataType m_initDataType;
    Cdm::SessionType m_licenseType;
    std::string m_sessionId;
    IMediaKeySessionCallback *m_piCallback;
};

}  // namespace CDMi
