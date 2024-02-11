var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();

var app = builder.Build();
app.UseRouting(); // ������� ��� ����� ��� ������������ �������������.

app.UseEndpoints(endpoints =>
{
    /*a) �������� ��������� ������� ��������:*/
    endpoints.MapControllerRoute(
    name: "custom",
    pattern: "custom/{controller}/{action}/{customParam}");
    /*b) ������� ��������:c) ������'����� ��������� ��������:(id)d) �������� ��������� �� �������������:
     controller=Home*/
    endpoints.MapControllerRoute(
        name: "default",
        pattern: "static/{controller=Home}/{action=Index}/{id?}");
    /*f) ��������� defaults ������ MapControllerRoute():*/
    endpoints.MapControllerRoute(
        name: "ID",
        pattern: "ID/{action}",
        defaults: new { controller = "ID" });
});


app.Run();