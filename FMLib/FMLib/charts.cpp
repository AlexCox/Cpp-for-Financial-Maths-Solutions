#include "charts.h"
#include "testing.h"

static void writeTopBoilerPlateOfPieChart(std::ostream& out) {
    out << "<html>\n";
    out << "<head>\n";
    out << "<!--Load the AJAX API-->\n";
    out << "<script type=\"text/javascript\"";
    out << "src=\"https://www.google.com/jsapi\">";
    out << "</script>\n";
    out << "<script type=\"text/javascript\">\n";
    out << "google.load('visualization', '1.0',";
    out << " {'packages':['corechart']});\n";
    out << "google.setOnLoadCallback(drawChart);\n";
    out << "function drawChart() {\n";
    out << "var data=new google.visualization.DataTable();";
    out << "\n";
    out << "data.addColumn('string', 'Label');\n";
    out << "data.addColumn('number', 'Value');\n";
}

static void writeBottomBoilerPlateOfPieChart(
    std::ostream& out) {
    out << "var options = {'title':'A Pie Chart',\n";
    out << "'width':400,\n";
    out << "'height':300\n";
    out << "};\n";
    out << "var chart = new google.visualization.PieChart(";
    out << "document.getElementById('chart_div'));\n";
    out << "chart.draw(data, options);\n";
    out << "}\n";
    out << "</script>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<div id='chart_div'>\n";
    out << "</body>\n";
    out << "</html>";
}

static void writeFixedPieChartData(std::ostream& out) {
    out << "data.addRows([\n";
    out << "['Bananas', 100],\n";
    out << "['Apples', 200],\n";
    out << "['Kumquats', 150]\n";
    out << "]);\n";
}

static void writeDataOfPieChart(std::ostream& out,
    const std::vector<std::string>& labels,
    const std::vector<double>& values) {
    size_t nLabels = labels.size();
    for (int i = 0; i < nLabels; i++) {
        std::string label = labels[i];
        double value = values[i];
        out << "['" << label << "', " << value << "]";
        if (i != nLabels - 1) {
            out << ", ";
        }
        out << "\n";
    }
}

static void testPieChartData() {
    std::stringstream out;
    std::vector<std::string> labels(3);
    std::vector<double> vals(3);
    for (int i = 0; i < 3; i++) {
        std::stringstream ss;
        ss << "A Label " << i;
        labels[i] = ss.str();
        INFO(labels[i]);
        vals[i] = (double)i;
    }
    writeDataOfPieChart(out, labels, vals);
    std::string asString = out.str();
    std::stringstream expected;
    expected << "data.addRows([\n";
    expected << "['A Label 0', 0],\n";
    expected << "['A Label 1', 1],\n";
    expected << "['A Label 2', 2]\n";
    expected << "]);\n";
    std::string expectedStr = expected.str();
    ASSERT(asString == expectedStr);
}

void pieChart(const std::string& file,
    const std::vector<std::string>& labels,
    const std::vector<double>& values) {
    std::ofstream out;
    out.open(file.c_str());
    writeTopBoilerPlateOfPieChart(out);
    writeDataOfPieChart(out, labels, values);
    writeBottomBoilerPlateOfPieChart(out);
    out.close();
}

void testFixedPieChart() {
    std::ofstream out;
    out.open("FixedPieChart.html");
    writeTopBoilerPlateOfPieChart(out);
    writeFixedPieChartData(out);
    writeBottomBoilerPlateOfPieChart(out);
    out.close();
}

void testCharts() {
    TEST(testFixedPieChart);
}