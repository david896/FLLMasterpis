using Microsoft.AspNetCore.Mvc;

namespace EspServer.Controllers;

[Route("api/[controller]")]
[ApiController]
public class BitmapController : ControllerBase
{
    [HttpGet]
    public IActionResult GetBitmap(string name)
    {
        switch (name)
        {
            case "Songs":
                return Ok(Bitmaps.Songs);
            case "Chords":
                return Ok(Bitmaps.Chords);
            case "Scales":
                return Ok(Bitmaps.Scales);
            case "Games":
                return Ok(Bitmaps.Games);
            case "Settings":
                return Ok(Bitmaps.Settings);
        }

        return BadRequest();
    }
}
