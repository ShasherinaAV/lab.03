#include "svg.h"
#include <windows.h>
#include <string>
#include<sstream>


void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg "
         << "width='" << width << "' "
         << "height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "' >"<< text <<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{

    cout << "<rect x='" << x <<"' y='" << y << "' width='" << width <<"' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}
string show_name_version ()
{
      stringstream buffer;
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD mask2 = 0x000000ff;
    DWORD version_major = version & mask2;
    DWORD version_minor = version >>8;

    if ((info & 0x40000000) == 0)
    {
        DWORD build = platform;
    }
    DWORD build = platform;

    buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    buffer << "Computer name: " << computer_name << "\n";
    return buffer.str();
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 600;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    const size_t MAX_VIDTH = IMAGE_WIDTH- TEXT_WIDTH;
    const size_t MAX_ASTERISK = 35;
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }

    for (size_t bin: bins)
    {
        double bin_factor ;
        const bool scalling_needed = max_count > MAX_ASTERISK;

        if (scalling_needed)
        {
            const double koeff = (double)MAX_ASTERISK / max_count;
            bin_factor= (size_t)(bin * koeff);
        }
        else {bin_factor=bin;}

        const double bin_width = BLOCK_WIDTH * bin_factor;

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#ffeeee");
        top += BIN_HEIGHT;
    }
    cout << "<text x='" << TEXT_LEFT << "' y='" << BIN_HEIGHT+top << "'>" << show_name_version() <<"</text>";
    svg_end();
}
