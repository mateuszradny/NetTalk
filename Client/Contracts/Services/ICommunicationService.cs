using NetTalk.Protocol.Requests;
using NetTalk.Protocol.Responses;
using System.Threading.Tasks;

namespace NetTalk.Contracts.Services
{
    public interface ICommunicationService
    {
        Task<ResponseBase> SendAsync(RequestBase request);
    }
}