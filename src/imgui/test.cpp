#include "colors.h"
#include "tableBuilder.hpp"
#include "logger.hpp"

#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

void draw_mockup_table()
{
  using colors::Green;
  using colors::Red;
  using cash_overflow::error::Error;

  tl::expected<cash_overflow::gui::Table, Error> table = cash_overflow::gui::Table::Builder{}
                                                           .with_id("Table")
                                                           .with_number_of_columns(4)
                                                           .with_headers({ "Account/Category", "Remaining Budget", "Change", "Total" })
                                                           .add_row({ "Assets", "", { "$-778.32", Red }, "$29,754.72" })
                                                           .add_row({ "|- Cash", "", { "$-2.85", Red }, "$236.30" })
                                                           .add_row({ "|- Checking Account", "", { "$-634.99", Red }, "$7,327.01" })
                                                           .add_row({ "|- Euro Account", "", { "-120.00 EUR", Red }, "5,403.00 EUR" })
                                                           .add_row({ "|- Investment Account", "", "0 CNY", "20,400.00 CNY" })
                                                           .add_row({ "|- Savings Account", "", "$0.00", "$12,800.00" })
                                                           .add_row({ "Liabilities", "", { "$-200.00", Green }, "$11,400.00" })
                                                           .add_row({ "|- Car Loan", "", { "$-200.00", Green }, "$11,400.00" })
                                                           .add_row({ "Incomes", "-", "$0.00", "$18,853.50" })
                                                           .add_row({ "|- Other", "-", "$0.00", "$5,853.50" })
                                                           .add_row({ "|- Salary", "-", "$0.00", "$13,000.00" })
                                                           .add_row({ "Expenses", { "$226.67 of $460.00", Green }, { "$578.32", Red }, "$4,532.67" })
                                                           .add_row({ "|- Bills", "-", { "$30.00", Red }, "$3,092.00" })
                                                           .add_row({ "|- Clothing", { "$-40.48 of $100.00", Red }, { "$140.48", Red }, "$949.48" })
                                                           .add_row({ "|- Groceries", { "$74.15 of $160.00", Green }, { "$85.85", Red }, "$155.20" })
                                                           .add_row({ "|- Leisure", { "$193.00 of $200.00", Green }, { "$7.00", Red }, "$21.00" })
                                                           .add_row({ "|- Other", "-", { "$314.99", Red }, "$314.99" })
                                                           .build();

  if (!table) {
    cash_overflow::gui::Text{ table.error().message, Red }.write();
  }
}

void draw_mockup()
{
  cash_overflow::gui::Window mockup{ "Mockup Table" };
  cash_overflow::gui::TabBar tab_bar{ "TabBar" };
  if (cash_overflow::gui::TabItem tab_item{ "Accounts & Categories" }) {
    draw_mockup_table();
  }
  if (cash_overflow::gui::TabItem tab_item{ "Expenses" }) {
    cash_overflow::gui::Text{ "Manga" }.write();
  }
  if (cash_overflow::gui::TabItem tab_item{ "Incomes" }) {
    cash_overflow::gui::Text{ "My income is €100k (daily)" }.write();
  }
  if (cash_overflow::gui::TabItem tab_item{ "Transfers" }) {
    cash_overflow::gui::Text{ "I transfered everything to the manga store" }.write();
  }
  if (cash_overflow::gui::TabItem tab_item{ "Securities" }) {
    cash_overflow::gui::Text{ "NullPointerException" }.write();
  }
  if (cash_overflow::gui::TabItem tab_item{ "Schedule" }) {
    cash_overflow::gui::Text{ "Minha criatividade já se acabou" }.write();
  }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "Cash Overflow");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  sf::CircleShape shape{ 100.F };
  shape.setFillColor(sf::Color::Cyan);
  shape.setPosition(sf::Vector2f{ 500.0, 350.0 });

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    draw_mockup();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }
  using LoggingLevel = cashoverflow::logging::LogLevel;
  auto &LOGGER = cashoverflow::logging::Logger::log(LoggingLevel::WARN);
  LOGGER.write("debug i dont print", LoggingLevel::DBG);
  LOGGER.write("warn i print", LoggingLevel::WARN);
  LOGGER.write("ERR i print", LoggingLevel::ERR);

  ImGui::SFML::Shutdown();

  return 0;
}
