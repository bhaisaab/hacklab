var React = require('react')
var ReactDOM = require('react-dom')

var HelloWorld = React.createClass({
  render: function() {
    return (
      <div>Hello {this.props.name}</div>
    )
  }
});

ReactDOM.render(
  <HelloWorld name="Rohit Yadav" />,
  document.getElementById('app')
);
