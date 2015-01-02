class CreateBookings < ActiveRecord::Migration
  def change
    create_table :bookings do |t|
      t.integer :user_id
      t.integer :room_id
      t.string :slots
      t.date :date

      t.timestamps
    end
  end
end
