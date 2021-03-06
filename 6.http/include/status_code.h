#ifndef HTTP_STATUS_CODE_H
#define HTTP_STATUS_CODE_H
#include <string>
#include <cstdint>

namespace http {

enum class StatusCode : uint16_t {
        None                            = 0,

        Continue                        = 100,
        SwitchingProtocol               = 101,
        Processing                      = 102,

        OK                              = 200,
        Created                         = 201,
        Accepted                        = 202,
        NonAuthorativeInformation       = 203,
        NoContent                       = 204,
        ResetContent                    = 205,
        PartialContent                  = 206,
        MultiStatus                     = 207,
        AlreadyReported                 = 208,
        IMUsed                          = 226,

        MultipleChoices                 = 300,
        MovedPermanently                = 301,
        Found                           = 302,
        SeeOther                        = 303,
        NotModified                     = 304,
        UseProxy                        = 305,
        UNUSED                          = 306,
        TemporaryRedirect               = 307,
        PermanentRedirect               = 308,

        BadRequest                      = 400,
        Unauthorized                    = 401,
        PaymentRequired                 = 402,
        Forbidden                       = 403,
        NotFound                        = 404,
        MethodNotAllowed                = 405,
        NotAcceptable                   = 406,
        ProxyAuthenticationRequired     = 407,
        RequestTimeout                  = 408,
        Conflict                        = 409,
        Gone                            = 410,
        LengthRequired                  = 411,
        PreconditionFailed              = 412,
        PayloadTooLarge                 = 413,
        URITooLong                      = 414,
        UnsupportedMediaType            = 415,
        RequestedRangeNotSatisfiable    = 416,
        ExpectationFailed               = 417,
        ImATeapot                       = 418,
        AuthenticationTimeout           = 419,
        MisdirectedRequest              = 421,
        UnprocessableEntity             = 422,
        Locked                          = 423,
        FailedDependency                = 424,
        UpgradeRequired                 = 426,
        PreconditionRequired            = 428,
        TooManyRequests                 = 429,
        RequestHeaderFieldsTooLarge     = 431,
        ConnectionClosedWithoutResponse = 444,
        RetryWith                       = 449,
        UnavailableForLegalReasons      = 451,
        ClientClosedRequest             = 499,

        InternalServerError             = 500,
        NotImplemented                  = 501,
        BadGateway                      = 502,
        ServiceUnavailable              = 503,
        GatewayTimeout                  = 504,
        HTTPVersionNotSupported         = 505,
        VariantAlsoNegotiates           = 506,
        InsufficientStorage             = 507,
        LoopDetected                    = 508,
        BandwidthLimitExceeded          = 509,
        NotExtended                     = 510,
        NetworkAuthenticationRequired   = 511,
        UnknownError                    = 520,
        WebServerIsDown                 = 521,
        ConnectionTimedOut              = 522,
        OriginIsUnreachable             = 523,
        ATimeoutOccured                 = 524,
        SSLHadnshakeFailed              = 525,
        NetworkConnectTimeoutError      = 599
};

std::string to_string(StatusCode code);

}  // namespace http

#endif  // HTTP_STATUS_CODE_H
