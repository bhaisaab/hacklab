var React = require('react')
var ReactDOM = require('react-dom')

var routes = require('./config/routes');

/*
var USER_DATA = {
  name: 'Rohit Yadav',
  username: 'rhtyd',
  image: 'https://avatars3.githubusercontent.com/u/95203?v=3&s=100'
}


var ProfilePic = React.createClass({
  render: function() {
    return <img src={this.props.imageUrl} />
  }
});

var Link = React.createClass({
  changeURL: function() {
    window.location.replace(this.props.href)
  },
  render: function() {
    return (
      <span
        style={{color: 'blue', cursor: 'pointer'}}
        onClick={this.changeURL}>
        {this.props.children}
      </span>
    )
  }
})

var ProfileLink = React.createClass({
    render: function() {
      return (
        <div>
          <Link href={'https://github.com/' + this.props.username}>
            {this.props.username}
          </Link>
        </div>
      )
    }
});


var ProfileName = React.createClass({
  render: function() {
    return (
      <div>{this.props.name}</div>
    )
  }
});

var Avatar = React.createClass({
  render: function() {
    return (
      <div>
        <ProfilePic imageUrl={this.props.user.image} />
        <ProfileName name={this.props.user.name} />
        <ProfileLink username={this.props.user.username} />
      </div>
    )
  }
})

var HelloWorld = React.createClass({
  render: function() {
    return (
      <div>Hello {this.props.name}</div>
    )
  }
});

ReactDOM.render(
  <Avatar user={USER_DATA} />,
  document.getElementById('app')
);
*/

ReactDOM.render(
  routes,
  document.getElementById('app')
);

