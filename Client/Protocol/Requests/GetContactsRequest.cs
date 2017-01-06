namespace NetTalk.Protocol.Requests
{
    public class GetContactsRequest : AuthenticatedRequest
    {
        public GetContactsRequest(string authToken) : base(authToken, RequestType.GetContacts)
        {
        }
    }
}